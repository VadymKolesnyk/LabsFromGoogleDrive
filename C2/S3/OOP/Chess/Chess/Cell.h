#pragma once

class Cell
{
public:
	Cell();
	Cell( char hor, int vert);
	Cell(const Cell& other);
	int GetVert() const;
	char GetHor() const;
	void SetCoord(char hor, int vert);
	Cell& operator =(const Cell& other);
	bool operator ==(const Cell& other) const;
	bool operator !=(const Cell& other) const;
	bool IsOnDesk();
	~Cell();
protected:
	int vert;
	char hor;
};
