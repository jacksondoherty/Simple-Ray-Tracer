#ifndef COLOR_H
#define COLOR_H

using namespace std;


class Color {
	public:
		float r;
		float g;
		float b;
		Color();
		Color(float r, float g, float b);
		Color(const Color &obj);
		Color& operator=(const Color &obj);
		Color operator*(const Color &obj) const;
		Color operator+(const Color &obj) const;
		Color scale(float s) const;
		void clamp();
		void print() const;
};

#endif /* COLOR_H */