#pragma once

template<typename CoordType>
struct Vector2 {
	CoordType X;
	CoordType Y;
};

template<typename CoordType>
struct Vector3 {
	CoordType X;
	CoordType Y;
	CoordType Z;
};

template<typename CoordType>
struct Vector4 {
	CoordType X;
	CoordType Y;
	CoordType Z;
	CoordType W;
};

template<typename ComponentType>
struct Color3 {
	ComponentType R;
	ComponentType G;
	ComponentType B;
};

template<typename ComponentType>
struct Color4 {
	ComponentType R;
	ComponentType G;
	ComponentType B;
	ComponentType A;
};