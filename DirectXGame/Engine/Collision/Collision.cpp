#include "Collision.h"
#include<cmath>

bool Collision::SphereToSphere(const myMath::Vector3& sphere1, float radius1, const myMath::Vector3& sphere2, float radius2)
{
	/*return false;

	if (std::pow((sphere2.x - sphere1.x), 2)
		+ std::pow((sphere2.y - sphere1.y), 2)
		+ std::pow((sphere2.z - sphere1.z), 2) <= std::pow((radius1 + radius2), 2))
	{
		return true;
	}*/

	if (std::pow((sphere2.x - sphere1.x), 2)
		+ std::pow((sphere2.y - sphere1.y), 2)
		+ std::pow((sphere2.z - sphere1.z), 2) <= std::pow((radius1 + radius2), 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToSphere(const Sphere* sphere1, const Sphere* sphere2)
{
	if (std::pow((sphere2->center.x - sphere1->center.x), 2)
		+ std::pow((sphere2->center.y - sphere1->center.y), 2)
		+ std::pow((sphere2->center.z - sphere1->center.z), 2) <= std::pow((sphere1->radius + sphere2->radius), 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToSphere(const Sphere& sphere1, const Sphere& sphere2)
{
	/*return false;

	if (std::pow((sphere2.center.x - sphere1.center.x), 2)
		+ std::pow((sphere2.center.y - sphere1.center.y), 2)
		+ std::pow((sphere2.center.z - sphere1.center.z), 2) <= std::pow((sphere1.radius + sphere2.radius), 2))
	{
		return true;
	}*/

	if (std::pow((sphere2.center.x - sphere1.center.x), 2)
		+ std::pow((sphere2.center.y - sphere1.center.y), 2)
		+ std::pow((sphere2.center.z - sphere1.center.z), 2) <= std::pow((sphere1.radius + sphere2.radius), 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToPlane(const Sphere& sphere, const Plane& plane, myMath::Vector3* inter)
{
	// 座標系の原点から球の中心座標への距離から
	// 平面の原点距離を減算することで、平面と球の中心との距離が出る
	float dist = sphere.center.dot(plane.normal) - plane.destance;
	// 距離の絶対値が半径より大きければ当たっていない
	if (fabsf(dist) > sphere.radius) return false;

	// 擬似交点を計算
	if (inter)
	{
		// 平面上の再接近点を、疑似交点とする
		*inter = -dist * plane.normal + sphere.center + sphere.center;
	}

	return true;
}

bool Collision::SphereToTriangle(const Sphere& sphere, const Triangle& triangle, myMath::Vector3* inter, myMath::Vector3* reject)
{
	myMath::Vector3 p;
	// 球の中心に対する最近接点である三角形上にある点pを見つける
	myMath::Vector3 tmp = sphere.center;
	ClosestPtPoint2Triangle(tmp, triangle, &p);
	// 点pと球の中心の差分ベクトル
	myMath::Vector3 v = p - sphere.center;
	// 距離の二乗を求める
	//（同じベクトル同士の内積は三平方の定理のルート内部の式と一致する）
	float distanceSquare = v.dot(v);
	// 球と三角形の距離が半径以下なら当たっていない
	if (distanceSquare > sphere.radius * sphere.radius)
	{
		return false;
	}

	// 擬似交点を計算
	if (inter)
	{
		// 三角形上の最近接点pを疑似交点とする
		*inter = p;
	}
	// 押し出すベクトルを計算
	if (reject)
	{
		float ds = sphere.center.dot(triangle.normal);
		float dt = triangle.p0.dot(triangle.normal);
		float rejectLen = dt - ds + sphere.radius;
		*reject = triangle.normal * rejectLen;
	}
	return true;
}

bool Collision::RayToPlane(const Ray& ray, Plane& plane, float* distance, myMath::Vector3* inter)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値

	float d1 = plane.normal.dot(ray.dir);
	// 裏面には当たらない
	if (d1 > -epsilon)
	{
		return false;
	}

	float d2 = plane.normal.dot(ray.start);
	float t = (plane.destance - d2) / d1;

	if (t < 0) return false;

	// 距離を書き込む
	if (distance)
	{
		*distance = t;
	}

	// 交点を計算
	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::RayToTriangle(const Ray& ray, const Triangle& triangle, float* distance, myMath::Vector3* inter)
{
	// 三角形が乗っている平面を算出
	Plane plane;
	myMath::Vector3 interPlane;
	myMath::Vector3 tmp = triangle.normal;
	plane.normal = tmp;
	plane.destance = triangle.normal.dot(triangle.p0);
	// レイと平面が当たっていなければ、当たっていない	
	if (!RayToPlane(ray, plane, distance, &interPlane))
	{
		return false;
	}
	// レイと平面が当たっていたので、距離と交点が書き込まれた

	// レイと平面の交点が三角形の内側にあるか判定
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	myMath::Vector3 m;
	// 辺p0_p1について
	myMath::Vector3 pt_p0 = triangle.p0 - interPlane;
	myMath::Vector3 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);
	// 辺の外側
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	// 辺p1_p2について
	myMath::Vector3 pt_p1 = triangle.p1 - interPlane;
	myMath::Vector3 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross(p1_p2);
	// 辺の外側
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	// 辺p2_p0について
	myMath::Vector3 pt_p2 = triangle.p2 - interPlane;
	myMath::Vector3 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross(p2_p0);
	// 辺の外側
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	if (inter)
	{
		*inter = interPlane;
	}

	// 内側なので、当たっている
	return true;
}

bool Collision::RayToSphere(const Ray& ray, const Sphere& sphere, float* distance, myMath::Vector3* inter)
{
	myMath::Vector3 m = ray.start - sphere.center;
	float b = m.dot(ray.dir);
	float c = m.dot(m) - sphere.radius * sphere.radius;
	// layの始点がsphereの外側にあり(c > 0)、layがsphereから離れていく方向を
	// 差している場合(b > 0)、当たらない
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	// 負の判別式はレイが球を外れていることに一致
	if (discr < 0.0f)
	{
		return false;
	}

	// レイは球と交差している。
	// 交差する最小の値tを計算
	float t = -b - sqrtf(discr);
	// tが負である場合、レイは球の内側から開始しているのでtをゼロにクランプ
	if (t < 0) t = 0.0f;

	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::RayToSphere(const myMath::Vector3& rayStartPos, const myMath::Vector3& rayEndPos, const myMath::Vector3& spherePos, float radius, float* distance)
{
	myMath::Vector3 m = rayStartPos - spherePos;
	myMath::Vector3 a = rayEndPos - rayStartPos;
	myMath::Vector3 d = a;
	a.normalization();
	float b = m.dot(a);
	float c = m.dot(m) - radius * radius;
	// layの始点がsphereの外側にあり(c > 0)、layがsphereから離れていく方向を
	// 差している場合(b > 0)、当たらない
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	// 負の判別式はレイが球を外れていることに一致
	if (discr < 0.0f)
	{
		return false;
	}

	// レイは球と交差している。
	// 交差する最小の値tを計算
	float t = -b - sqrtf(discr);
	// tが負である場合、レイは球の内側から開始しているのでtをゼロにクランプ
	if (t < 0) t = 0.0f;

	if (distance)
	{
		*distance = t;
	}

	if (d.length() < t)
	{
		return false;
	}

	return true;
}

void Collision::ClosestPtPoint2Triangle(const myMath::Vector3& point, const Triangle& triangle, myMath::Vector3* closest)
{
	// pointがp0の外側の頂点領域の中にあるかどうかチェック
	myMath::Vector3 p0_p1 = triangle.p1 - triangle.p0;
	myMath::Vector3 p0_p2 = triangle.p2 - triangle.p0;
	myMath::Vector3 p0_pt = point - triangle.p0;

	float d1 = p0_pt.dot(p0_p1);
	float d2 = p0_pt.dot(p0_p2);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0が最近傍
		*closest = triangle.p0;
		return;
	}

	// pointがp1の外側の頂点領域の中にあるかどうかチェック
	myMath::Vector3 p1_pt = point - triangle.p1;

	float d3 = p1_pt.dot(p0_p1);
	float d4 = p1_pt.dot(p0_p2);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1が最近傍
		*closest = triangle.p1;
		return;
	}

	// pointがp0_p1の辺領域の中にあるかどうかチェックし、あればpointのp0_p1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// pointがp2の外側の頂点領域の中にあるかどうかチェック
	myMath::Vector3 p2_pt = point - triangle.p2;

	float d5 = p2_pt.dot(p0_p1);
	float d6 = p2_pt.dot(p0_p2);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// pointがp0_p2の辺領域の中にあるかどうかチェックし、あればpointのp0_p2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// pointがp1_p2の辺領域の中にあるかどうかチェックし、あればpointのp1_p2上に対する射影を返す
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	// pointは面領域の中にある。closestを重心座標を用いて計算する
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}
