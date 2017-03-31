#pragma once

#include <StateSpace.hpp>
#include <vector>

namespace RRT {

/**
 * @brief Reduce the vector to @maxSize length
 * @details We do this by sampling to evenly distribute deletions
 *
 * @param states     The vector of T values to sample
 * @param maxSize Max length of the resulting vector
 */
template <typename T>
void DownSampleVector(std::vector<T>& states, size_t maxSize) {
    if (states.size() > maxSize) {
        int toDelete = states.size() - maxSize;
        float spacing = (float)states.size() / (float)toDelete;
        float i = 0.0;
        while (toDelete) {
            toDelete--;
            states.erase(states.begin() + (int)(i + 0.5));
            i += spacing - 1.0;
        }
    }
}

template <typename T>
void SuperSampleVector(std::vector<T>& states, size_t pointsBetween) {
    std::vector<T> newStates;
    for(unsigned i = 1; i < states.size(); ++i) {
        float a = (states[i].y-states[i-1].y)/(states[i].x-states[i-1].x);
        float b = states[i].y - a*states[i].x;
        for(unsigned j = 0; j <= pointsBetween; ++j) {
            float x = (float)j*(states[i].x-states[i-1].x)/pointsBetween + states[i-1].x;
            float y = a*x+b;
            newStates.push_back(T(x,y));
        }
    }
    states = newStates;
}

/**
 * @brief Deletes waypoints from @pts
 *
 * @param pts A vector of states that constitutes the path
 * @param transitionValidator A function that returns a boolean indicating
 *        whether or not a straight connection exists between the two given
 * states
 */
template <typename T>
void SmoothPath(std::vector<T>& pts, const StateSpace<T>& stateSpace) {
    int span = 2;
    while (span < pts.size()) {
        bool changed = false;
        for (int i = 0; i + span < pts.size(); i++) {
            if (stateSpace.transitionValid(pts[i], pts[i + span])) {
                for (int x = 1; x < span; x++) {
                    pts.erase(pts.begin() + i + 1);
                }
                changed = true;
            }
        }

        if (!changed) span++;
    }
}

// Number of intermediate points between two source ones,
// Actually, this value should be calculated in some way,
// Obviously, depending on the real length of the curve.
// But I don't know any elegant and fast solution for this
// problem.
#define NUM_STEPS 20

template <typename T>
void curve4(std::vector<T> & path,  
            double x1, double y1, //Anchor1
            double x2, double y2,   //Control1
            double x3, double y3,   //Control2
            double x4, double y4)   //Anchor2
{

    double subdiv_step  = 1.0 / (NUM_STEPS + 1);
    double subdiv_step2 = subdiv_step*subdiv_step;
    double subdiv_step3 = subdiv_step*subdiv_step*subdiv_step;

    double pre1 = 3.0 * subdiv_step;
    double pre2 = 3.0 * subdiv_step2;
    double pre4 = 6.0 * subdiv_step2;
    double pre5 = 6.0 * subdiv_step3;

    double tmp1x = x1 - x2 * 2.0 + x3;
    double tmp1y = y1 - y2 * 2.0 + y3;

    double tmp2x = (x2 - x3)*3.0 - x1 + x4;
    double tmp2y = (y2 - y3)*3.0 - y1 + y4;

    double fx = x1;
    double fy = y1;

    double dfx = (x2 - x1)*pre1 + tmp1x*pre2 + tmp2x*subdiv_step3;
    double dfy = (y2 - y1)*pre1 + tmp1y*pre2 + tmp2y*subdiv_step3;

    double ddfx = tmp1x*pre4 + tmp2x*pre5;
    double ddfy = tmp1y*pre4 + tmp2y*pre5;

    double dddfx = tmp2x*pre5;
    double dddfy = tmp2y*pre5;

    int step = NUM_STEPS;

    // Suppose, we have some abstract object Polygon which
    // has method AddVertex(x, y), similar to LineTo in
    // many graphical APIs.
    // Note, that the loop has only operation add!
    while(step--)
    {
        fx   += dfx;
        fy   += dfy;
        dfx  += ddfx;
        dfy  += ddfy;
        ddfx += dddfx;
        ddfy += dddfy;
        path.push_back(T(fx,fy));
    }
    path.push_back(T(x4,y4));
}

template <typename T>
void SmoothEdges(std::vector<T>& pts, const StateSpace<T>& stateSpace) {
  RRT::SuperSampleVector(pts,8);
      for(unsigned i = 4; i < pts.size(); i++) {
        float a1 = (pts[i].y-pts[i-4].y)/(pts[i].x-pts[i-4].x);
        float a2 = (pts[i-1].y-pts[i-3].y)/(pts[i-1].x-pts[i-3].x);
        if(std::abs(a1 - a2) > 0.001){
            if(stateSpace.transitionValid(pts[i], pts[i-4])){
                pts.erase(pts.begin()+i-3);
                pts.erase(pts.begin()+i-2);
                pts.erase(pts.begin()+i-1);
            }else if(stateSpace.transitionValid(pts[i-1], pts[i-3])){
                pts.erase(pts.begin()+i-2);
            }
        }
        //RRT::curve4(test,path[i-3].x,path[i-3].y,path[i-2].x,path[i-2].y,
        //                          path[i-1].x,path[i-1].y,path[i].x,path[i].y);
    }  
}

template <typename T>
void SmoothEdges2(std::vector<T>& pts, const StateSpace<T>& stateSpace) {
  RRT::SuperSampleVector(pts,10);
      for(unsigned i = 0; i < pts.size(); i++) {
        for(unsigned j = i+1; j < pts.size(); j++ ){
            if(stateSpace.transitionValid(pts[i], pts[j])){
                unsigned pos = i+1;
                for(unsigned k = i+1;k<j;k++){
                    pts.erase(pts.begin()+pos);
                }
            }
        }
    }  
}

}  // namespace RRT
