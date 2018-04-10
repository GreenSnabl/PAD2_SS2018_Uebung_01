/* 
 * File:   Screen.h
 * Author: mroth
 *
 * Created on 20. März 2018, 16:02
 */

#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
using std::ostream;
#include <vector>
using std::vector;
#include <string>
using std::string;

class Screen
{
public:
	struct Pos2d
	{
		int x;
		int y;
	};

	Screen(int width, int height);
	Screen(const Screen& other);
	virtual ~Screen();

	char getChar(Pos2d pos) const;
	char& getChar(Pos2d pos);
	void setChar(Pos2d pos, char c);

        void setVisibility(bool visibile);
        bool getVisibility() const;
        
	void setString(Pos2d pos, const string& item);
	void setInt(Pos2d pos, const int& item);

	void fill(char c);

	void draw();

	void addSubScreen(Screen* subs, Pos2d anchor, const string& name);
	Screen* getSubScreen(const string& name);
        void setAnchor(Pos2d anchor);
        
        bool deleteSubScreen(const string& name);        
        void clearSubScreens();

private:
	const int m_width;
	const int m_height;
	char* m_screen;
        
        bool m_visible;
        
	string m_name;
	Pos2d m_anchor;
	vector<Screen*> m_screens;
	
protected:
	void draw(Screen& s);
};

#endif /* SCREEN_H */

