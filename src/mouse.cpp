/**
 * @file mouse.cpp
 * @author Nishad Kulkarni, Sparsh Jaiswal, Divyansh Agrawal
 * @brief 
 * @version 3.14
 * @date 2021-11-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool rwa2::Mouse::search_maze(std::vector<int> n,std::vector<int> g){
    if(n != g){
        if(s.empty()){
            s.push(n);                                  //check if stack is empty and push current location directly into stack without changing
        }
    }

    else{
        return true;                                    //current node is goal node
    }

    if(!(vector_element_check(n))){
        v.push_back(n);                                 //if node is not in visited vector list v, push it into v
    }


    //if else ladder to check next node. Path is decided by checking in order NORTH, EAST, SOUTH, WEST
    if((!(m_maze.at(n.at(0)).at(n.at(1)).is_wall(direction::NORTH))) && (n.at(1)+1>=0) && (n.at(1)+1<m_maze_height) && !(vector_element_check({n.at(0),n.at(1)+1}))){
        n.at(1) += 1;
        s.push(n);
    }

    else if((!(m_maze.at(n.at(0)).at(n.at(1)).is_wall(direction::EAST))) && (n.at(0)+1>=0) && (n.at(0)+1<m_maze_width) && !(vector_element_check({n.at(0)+1,n.at(1)}))){
        n.at(0) += 1;
        s.push(n);
    }

    else if((!(m_maze.at(n.at(0)).at(n.at(1)).is_wall(direction::SOUTH))) && (n.at(1)-1>=0) && (n.at(1)-1<m_maze_height) && !(vector_element_check({n.at(0),n.at(1)-1}))){
        n.at(1) -= 1;
        s.push(n);
    }

    else if((!(m_maze.at(n.at(0)).at(n.at(1)).is_wall(direction::WEST))) && (n.at(0)-1>=0) && !(vector_element_check({n.at(0)-1,n.at(1)}))){
        n.at(0) -= 1;
        s.push(n);
    }

    else{
        if(!(s.empty())){
            s.pop();        //if no path found backtrack to previous node
        }
        else{
            return false;   //no path possible
        }
    }

    if(!(s.empty())){
        n = s.top();                //new node is the node on top of stack
        return search_maze(n,g);    //search path from new updated node n
    }
    else{
        return false;               //no path possible
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rwa2::Mouse::move_forward(){
    API::moveForward();             //use method from API to make mouse move forward
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rwa2::Mouse::turn_left(){
    API::turnLeft();                //use method from API to make mouse turn left
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rwa2::Mouse::turn_right(){
    API::turnRight();               //use method from API to make mouse turn right
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rwa2::Mouse::wall_checker(){

    std::array<char, 4> directions{'n','e','s','w'};

    if(m_direction==direction::NORTH){                                          //check walls when facing NORTH
        m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, API::wallFront());
        m_maze.at(m_x).at(m_y).set_wall(direction::EAST, API::wallRight());
        m_maze.at(m_x).at(m_y).set_wall(direction::WEST, API::wallLeft());
    }

    else if(m_direction==direction::EAST){                                      //check walls when facng EAST
        m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, API::wallLeft());
        m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, API::wallRight());
        m_maze.at(m_x).at(m_y).set_wall(direction::EAST, API::wallFront());
    }

    else if(m_direction==direction::SOUTH){                                     //check walls when facing SOUTH
        m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, API::wallFront());
        m_maze.at(m_x).at(m_y).set_wall(direction::WEST, API::wallRight());
        m_maze.at(m_x).at(m_y).set_wall(direction::EAST, API::wallLeft());
    }

    else if(m_direction==direction::WEST){                                       //check walls when facing WEST
        m_maze.at(m_x).at(m_y).set_wall(direction::WEST, API::wallFront());
        m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, API::wallRight());
        m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, API::wallLeft());
    }

    for(int i{0};i<4;i++){
        if(m_maze.at(m_x).at(m_y).is_wall(i)){
            API::setWall(m_x,m_y,directions.at(i));                              //set walls
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<int>> rwa2::Mouse::dfs_path(){                          
    std::vector<std::vector<int>> dfs;
    while(!(s.empty())){
        dfs.push_back(s.top());                                                  //get elements from stack s and return them into a vector
        s.pop();
    }

    std::reverse(dfs.begin(),dfs.end());                                         //reverse the vector dfs. This function is found in <algorithm>
    return dfs;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rwa2::Mouse::mouse_mover(std::vector<std::vector<int>> abc){
    for(int i{0};i<abc.size()-1;i++){
        wall_checker();

        //Move from North..
        if(m_direction==direction::NORTH){
            if((abc.at(i+1).at(1)==abc.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH))){        //..to next node at NORTH 
                move_forward();
                m_y+=1;
                m_direction = direction::NORTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST))){    //..to next node at EAST
                turn_right();
                move_forward();
                m_x+=1;
                m_direction = direction::EAST;
            }
            else if((abc.at(i+1).at(1)==abc.at(i).at(1) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH))){   //..to next node at SOUTH
                turn_left();
                turn_left();
                move_forward();
                m_y-=1;
                m_direction = direction::SOUTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST))){    //..to next node at WEST
                turn_left();
                move_forward();
                m_x-=1;
                m_direction = direction::WEST;
            }
            else{
                break;                                                                                        //cannot move so break out of loop
            }
        }
        //Move from EAST..
        else if(m_direction==direction::EAST){
            if((abc.at(i+1).at(1)==abc.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH))){            //..to next node at NORTH
                turn_left();
                move_forward();
                m_y+=1;
                m_direction = direction::NORTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) + 1 ) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST))){       //..to next node at EAST
                move_forward();
                m_x+=1;
                m_direction = direction::EAST;
            }
            else if((abc.at(i+1).at(1)==abc.at(i).at(1) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH))){       //..to next node at SOUTH
                turn_right();
                move_forward();
                m_y-=1;
                m_direction = direction::SOUTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST))){        //..to next node at WEST
                turn_left();
                turn_left();
                move_forward();
                m_x-=1;
                m_direction = direction::WEST;
            }
            else{
                break;                                                                                             //cannot move so break out of loop
            }
        }
        //move from SOUTH
        else if(m_direction==direction::SOUTH){
            if((abc.at(i+1).at(1)==abc.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH))){            //..to next node at NORTH
                turn_left();
                turn_left();
                move_forward();
                m_y+=1;
                m_direction = direction::NORTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST))){        //..to next node at EAST
                turn_left();
                move_forward();
                m_x+=1;
                m_direction = direction::EAST;
            }
            else if((abc.at(i+1).at(1)==abc.at(i).at(1) - 1 ) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH))){      //..to next node at SOUTH
                move_forward();
                m_y-=1;
                m_direction = direction::SOUTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) - 1 ) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST))){       //..to next node at WEST
                turn_right();
                move_forward();
                m_x-=1;
                m_direction = direction::WEST;
            }
            else{
                break;                                                                                              //cannot move so break out of loop
            }
        }
        //move from west
        else if(m_direction==direction::WEST){
            if((abc.at(i+1).at(1)==abc.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH))){            //..to next node at NORTH
                turn_right();
                move_forward();
                m_y+=1;
                m_direction = direction::NORTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST))){        //..to next node at EAST
                turn_left();
                turn_left();
                move_forward();
                m_x+=1;
                m_direction = direction::EAST;
            }
            else if((abc.at(i+1).at(1)==abc.at(i).at(1) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH))){       //..to next node at SOUTH
                turn_left();
                move_forward();
                m_y-=1;
                m_direction = direction::SOUTH;
            }
            else if((abc.at(i+1).at(0)==abc.at(i).at(0) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST))){        //..to next node at WEST
                move_forward();
                m_x-=1;
                m_direction = direction::WEST;
            }
            else{
                break;                                                                                              //cannot move so break out of loop
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<int> rwa2::Mouse::current_location(){
    std::vector<int> c_loc{m_x, m_y};
    return c_loc;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rwa2::Mouse::clear_visited(){
    v.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool rwa2::Mouse::vector_element_check(std::vector<int> e){
    for(int i{0};i<v.size();i++){
        if(v.at(i)==e){
            return true;                                               //returns true and exits function if element is found
        }
    }
    return false;                                                      //returns false as no element found
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rwa2::Mouse::path_highlighter(std::vector<std::vector<int>> path,std::vector<int> g)
{
    std::vector<int> h;

    for (int i{1}; i < path.size(); i++)
    {
        h = path.at(i);
        if (h != g)
        {
            API::setColor(h.at(0), h.at(1), 'c');
        }
    }
}