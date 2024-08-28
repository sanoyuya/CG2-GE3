#include "GameScene.h"
#include"GameHeader.h"
#include"SceneChangeAnimation.h"
#include"EasingFunction.h"
#include <algorithm>
#include<cpprest/filestream.h>
#include<cpprest/http_client.h>
#include<imgui.h>
#include <codecvt>

using namespace utility;//文字列変換などの一般的なユーティリティ
using namespace web;//URIのような共通な機能
using namespace web::http;//共通のHTTP機能
using namespace web::http::client;//HTTPクライアントの機能
using namespace concurrency::streams;//非同期ストリーム

std::string wstringToString(const std::wstring& wstr) {
	std::string str(wstr.begin(), wstr.end());
	return str;
}

template<class T>
pplx::task<T>Get(const std::wstring& url, std::wstring& token_)
{
	return pplx::create_task([=]
		{
			http_client client(url);
			http_request req(methods::GET);
			req.headers().add(L"Authorization",L"Bearer " + token_);
			return client.request(req);
		}).then([](http_response response)
			{
				if (response.status_code() == status_codes::OK)
				{
					return response.extract_json();
				}
				else
				{
					throw std::runtime_error("Received non-OK HTTP status code");
				}
			});
}

pplx::task<int>Post(const std::wstring& url,int32_t score, std::wstring& token_)
{
	return pplx::create_task([=]
		{
			json::value postData;
			postData[L"score"] = score;

			http_request req(methods::POST);
			req.headers().add(L"Authorization", L"Bearer " + token_);
			req.headers().add(L"Content-Type", L"application/json");
			req.set_body(postData.serialize());

			http_client client(url);
			return client.request(req); }).then([&](http_response response)
				{
					if (response.status_code() == status_codes::OK)
					{
						return response.extract_json();
					}
					else
					{
						throw std::runtime_error("Received non-OK HTTP status code");
					}}).then([](json::value json) {
						return json[L"status_code"].as_integer();
						});	
}

pplx::task<int>Login(const std::wstring& url, std::wstring& token)
{
	return pplx::create_task([=]
		{
			json::value postData;

			postData[L"name"] = json::value::string(L"sano100");
			postData[L"password"] = json::value::string(L"password");

			http_client client(url);
			return client.request(methods::POST, L"", postData.serialize(), L"application/json");
		}).then([](http_response response)
			{
				if (response.status_code() == status_codes::OK)
				{
					return response.extract_json();
				}
				else
				{
					throw std::runtime_error("Received non-OK HTTP status code");
				}
			}).then([&](json::value json)
				{
					token = json[L"token"].as_string();
					std::wstring status = json[L"login_status"].as_string();
					if (status == L"success")
					{
						return 1;
					}
					else
					{
						return 0;
					}
				});
}

void GameScene::Initialize()
{
	input_ = InputManager::GetInstance();

	gameTimer_ = std::make_unique<GameTimer>();

	period = std::make_unique<Sprite2D>();
	periodTex_= TextureManager::GetInstance()->LoadTexture("Resources/default/period.png");
	period->Sprite2DInitialize(periodTex_);

	numberTex_ = TextureManager::GetInstance()->LoadTexture("Resources/default/number.png");
	for (uint8_t i = 0; i < 7; i++)
	{
		if (i < 3)
		{
			timeSprite_[i] = std::make_unique<Sprite2D>();
			timeSprite_[i]->Sprite2DInitialize(numberTex_);
			timeStrNum[i] = 48;
		}

		time2Sprite_[i] = std::make_unique<Sprite2D>();
		time2Sprite_[i]->Sprite2DInitialize(numberTex_);

		time2StrNum[i] = 48;

		scoreSprite_[i] = std::make_unique<Sprite2D>();
		scoreSprite_[i]->Sprite2DInitialize(numberTex_);
		scoreStrNum_[i] = 48;
	}
}

void GameScene::Destroy()
{

}

void GameScene::Update()
{
	switch (modeFlag_)
	{
	case Mode::START:

		if (input_->KeyboardTriggerPush(DIK_SPACE))
		{
			modeFlag_ = Mode::GAME;
		}

		break;
	case Mode::GAME:

		if (input_->KeyboardTriggerPush(DIK_SPACE))
		{
			modeFlag_ = Mode::END;
		}

		gameTimer_->Update();

		time_ = gameTimer_->GetIntTime();
		DigitCalculation(time_, timeDig_);
		sprintf_s(timeStrNum, sizeof(timeStrNum), "%d", time_);
		sprintf_s(time2StrNum, sizeof(time2StrNum), "%d", static_cast<int>((gameTimer_->GetFlameCount() - gameTimer_->GetIntTime() * 60) / 60 * 100000));

		score_ = 999999 - static_cast<int>(sqrt((600 - gameTimer_->GetFlameCount()) * (600 - gameTimer_->GetFlameCount())) * 1666.665);
		score_ = std::clamp(score_, static_cast<int32_t>(0), static_cast<int32_t>(999999));

		sprintf_s(scoreStrNum_, sizeof(scoreStrNum_), "%d", score_);
		DigitCalculation(score_, scoreDig_);

		if (180 <= gameTimer_->GetFlameCount() && gameTimer_->GetFlameCount() <= 240)
		{
			alpha_ = static_cast<float>(Easing::EaseInCubic(gameTimer_->GetFlameCount()- 180, 1.0f, 0.0f, 60));
		}

		break;
	case Mode::END:

		alpha_ = 1.0f;

		if (isLogin_ == false)
		{
			if (input_->KeyboardTriggerPush(DIK_SPACE))
			{
				isConect_ = true;
			}
		}

		//APIに通信する
		if (isConect_ == true)
		{
			try 
			{
				auto loginStatus = Login(L"https://swgame-sanoyuyas-projects.vercel.app/users/login",token_).wait();
				if (loginStatus == 1)
				{
					isLogin_ = true;
					isConect_ = false;
					ImGui::Text("SUCCESS\n");
				}
			}
			catch (const std::exception& e)
			{
				ImGui::Text("Error exception:%s\n", e.what());
			}

			if (isLogin_ == true)
			{
				try
				{
					auto serverStatusCode = Post(L"https://swgame-sanoyuyas-projects.vercel.app/scores", score_,token_).wait();

					//スコアの登録が完了したら、ランキングを取得する。POSTがうまくいくと1が返ってくる
					if (serverStatusCode == 1)
					{
						//投稿に成功したらGET通信でランキングを取得する
						auto task = Get<json::value>(L"https://swgame-sanoyuyas-projects.vercel.app/scores", token_);
						const json::value j = task.get();
						auto array = j.as_array();

						//JSONオブジェクトから必要部分を切り出してint型の配列に代入
						for (int i = 0; i < array.size(); i++)
						{
							rank_[i].name = wstringToString(array[i].at(U("user")).at(U("name")).as_string());
							rank_[i].score = array[i].at(U("score")).as_integer();
						}
						isConect_ = false;
					}
				}
				catch (const std::exception& e)
				{
					ImGui::Text("Error exception:%s\n", e.what());
				}
			}
		}
		else
		{
			if (input_->KeyboardTriggerPush(DIK_SPACE))
			{
				modeFlag_ = Mode::RESULT;
			}
		}

		break;
	case Mode::RESULT:

		if (input_->KeyboardTriggerPush(DIK_SPACE))
		{
			SceneChangeAnimation::GetInstance()->Change("TITLE");
		}

		ImGui::Begin("ranking");
		ImGui::Text("1st : %d", rank_[0].score);
		ImGui::Text("2nd : %d", rank_[1].score);
		ImGui::Text("3rd : %d", rank_[2].score);
		ImGui::Text("4th : %d", rank_[3].score);
		ImGui::Text("5th : %d", rank_[4].score);
		ImGui::End();
		break;
	default:
		break;
	}

	gameTimer_->ImGuiUpdate();
}

void GameScene::Draw()
{
	uint16_t num = 0;
	float scale = 2.0f;
	float interval = 40.0f * scale;

	for (uint8_t i = 0; i < timeDig_; i++)
	{
		num = timeStrNum[i] - 48;
		timeSprite_[i]->DrawAnimationSpriteX2D({ i * interval + 700.0f - interval * timeDig_,GameHeader::windowsCenter_.y - 24.0f }, 10, num, { 1.0f,1.0f ,1.0f ,alpha_ }, { scale ,scale });
	}

	scale = 1.0f;
	interval = 40.0f * scale;

	for (uint8_t i = 0; i < maxDig_-1; i++)
	{
		num = time2StrNum[i] - 48;
		time2Sprite_[i]->DrawAnimationSpriteX2D({ i * interval + 1000.0f - interval * maxDig_,GameHeader::windowsCenter_.y +12.0f }, 10, num, { 1.0f,1.0f ,1.0f ,alpha_ }, { scale ,scale });
	}

	period->DrawSprite2D({ 700.0f ,GameHeader::windowsCenter_.y + 24.0f }, { 1.0f,1.0f ,1.0f ,alpha_ }, { scale ,scale });

	if (modeFlag_ == Mode::END)
	{
		for (uint8_t i = 0; i < scoreDig_; i++)
		{
			num = scoreStrNum_[i] - 48;
			scoreSprite_[i]->DrawAnimationSpriteX2D({ i * interval + 700.0f - interval * scoreDig_,GameHeader::windowsCenter_.y +300.0f }, 10, num, { 1.0f,1.0f ,1.0f ,1.0f }, { scale ,scale });
		}
	}

	SceneChangeAnimation::GetInstance()->Draw();
}

void GameScene::DigitCalculation(uint32_t num, uint8_t& digit)
{
	if (num <= 9)digit = 1;
	else if (10 <= num && num < 100)digit = 2;
	else if (100 <= num && num < 1000)digit = 3;
	else if (1000 <= num && num < 10000)digit = 4;
	else if (10000 <= num && num < 100000)digit = 5;
	else if (100000 <= num && num < 1000000)digit = 6;
	else digit = 7;
}