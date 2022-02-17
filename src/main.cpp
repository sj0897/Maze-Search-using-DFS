/**
 * @file main.cpp
 * @author Nishad Kulkarni, Sparsh Jaiswal, Divyansh Agrawal
 * @brief 
 * @version 3.14
 * @date 2021-11-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <iostream>
#include <array>
#include <string>

#include "../include/mouse/mouse.h"
#include "../include/api/api.h"


int main() {
    rwa2::Mouse mouse;                                       //create object 'mouse' of class type 'Mouse from namespace'rwa2' using default constructor
    mouse.display_walls();                                   //call display walls to display the border walls

    std::vector<int> g1{7,7};                                //Set goal node co-ordinates
    std::vector<int>c_loc = mouse.current_location();        //get current(start) location co-ordinates of the mouse 

    API::setText(c_loc.at(0),c_loc.at(1),"START");           //Set start node name as Start

    while(true){                                        //do continuously
        
        API::clearAllColor();                                   //clear all tiles' color
        API::setColor(g1.at(0),g1.at(1),'g');                   //set goal node color as green
        API::setText(g1.at(0),g1.at(1),"G1");                   //set goal node text as 'G1'

        std::vector<int>c_loc = mouse.current_location();

        API::setColor(c_loc.at(0),c_loc.at(1),'r');             //set current starting node color as red
        
        std::cerr<<"current location is: "<<c_loc.at(0)<<","<<c_loc.at(1)<<std::endl;       //show current node co-ordinates on the simulator

        mouse.wall_checker();                                   //check all the walls and update them in mouse.m_maze

        if(c_loc==g1){                                          //check if reached goal
            std::cerr<<"Reached goal!"<<std::endl;              //Show in simulator that the mouse has reached the goal
            API::clearAllColor();                               //clear all tiles' color
            API::setColor(g1.at(0),g1.at(1),'g');               //set goal node color as green
            API::setText(g1.at(0),g1.at(1),"G1");               //set goal node text as G1
            break;                                              //exit from while loop as mouse has reached goal
        }

        bool is_path = mouse.search_maze(c_loc,g1);             //search path from current node

        std::vector<std::vector<int>> dfs = mouse.dfs_path();   //get the dfs path to be followed by the mouse

        mouse.path_highlighter(dfs,g1);                         //highlight the dfs path to reach goal
        
        mouse.mouse_mover(dfs);                                 //make the mouse move along the dfs path

        mouse.clear_visited();                                  //clear previously visited nodes
    }
}

