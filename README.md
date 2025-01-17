# YamoEngine
DirectX12を使用した自作エンジン

## 2D及び3Dの描画機能
### 2D描画の機能
* スプライト描画
* 画像切り抜き描画
* 連番画像描画(2Dアニメーション)
* ブレンドモードの変更(6種類)

### 3D描画の機能
* objファイルの読み込み
* assimpを使用したgltfファイルの読み込み
* モデルの描画
* ブレンドモードの変更(6種類)
* シェーダーモードの変更  
※新しいシェーダーを追加する際はシェーダーオブジェクトを増やしてから、DrawCommon::ShaderCompile()を使用し、各シェーダーを読み込む必要があります。

### ライト
* 平行光源
* 点光源
* スポットライト

### ポストエフェクト  
* ガウシアンブラー
* UVシフト
* 明度2倍
* 色反転
* グレースケール
* セピアカラー
* ポストエフェクトの切り替え  
※新しいシェーダーを追加する際はシェーダーオブジェクトを増やしてから、DrawCommon::ShaderCompile()を使用し、各シェーダーを読み込む必要があります。

## その他の機能
### 対応入力デバイス
DirectInput,XInputを使用して実装しています。
* キーボード
* マウス
* コントローラー

### オーディオ
XAudio2を使用して実装しています。
* 音の再生
* 音の停止
* 音量調節

YamoEngineではイージング関数や数学関数があり、ユーザーの開発をサポートする機能が実装されています。  
詳細な使用方法は各ヘッダーファイルを参照してください。

## 使用外部ライブラリ
* DirectXTex
* ImGui
* assimp
* json.hpp

## 推奨環境
Windows10  
※Windows11では正常に動作しない可能性があります。
