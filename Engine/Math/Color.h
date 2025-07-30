#pragma once
// »ö»ó
enum class Color : int
{
	Blue = 1,
	Green = 2,
	Red = 4,
	White = Red | Green | Blue, // = 7,
	Intensity = 8
};