/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
vector<std::string> Split(string str,char determine) {
  size_t last = 0;
  vector<string> substrs;
  int special=1;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str[i] == determine) {
      string substr = str.substr(last, i - last);
      last = i + 2;
      substrs.push_back(substr);
    }
  }
  std::string substr = str.substr(last, str.length() - last);
  substrs.push_back(substr);
  return substrs;
}

V2D file_to_V2D(const std::string & filename){
    // Your code here!
    V2D data;
    ifstream data_file(filename);
    string word;
    if (data_file.is_open()) {
        while (getline(data_file, word)) {
            data.push_back(Split(word,','));
        }
    }
    return data;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    V2D answer;
    for(auto course:cv){
        vector<string> temp;
        temp.push_back(course[0]);
        for (size_t p=1;p<course.size();p++){
            for(auto single:student){
                if(course[p]!=single[0]){
                    continue;
                }
                for(size_t i=1;i<single.size();i++){
                    if(single[i]==course[0]){
                        temp.push_back(single[0]);
                        break;
                    }
                }
            }                 
        }
        if(temp.size()>1){
            answer.push_back(temp);
        }
    }
return answer;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
bool confliction(vector<string> course1,vector<string> course2){
    for(size_t i=1;i<course1.size();i++){//student
        for(size_t j=1;j<course2.size();j++){
            if(course1[i]==course2[j]){
                return true;
            }
        }
    }
    return false;
}
// map<string,vector<string>> getVertice(const V2D &courses,map<string,int>& colors){
//     map<string,vector<string>> Vertice;
//     for(auto course:courses){
//         colors[course[0]]=0;
//         Vertice[course[0]]=vector<string>();
//         for(auto compare:courses){
//             if(compare==course){
//                 continue;
//             }
//             if(confliction(course,compare)){
//                 Vertice[course[0]].push_back(compare[0]);
//                 continue;
//             }

//         }
//     }
//     return Vertice;
// }

// bool confliction=false;
// for(size_t i=1;i<course.size();i++){//student
//     for(size_t j=1;j<compare.size();j++){
//         if(course[i]==compare[j]){
//             confliction=true;
//             break;
//         }
//     }
//     if(confliction) break;
// }
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    map<string,int>colors; 
    map<string,vector<string>> Vertice;
    for(auto course:courses){
        colors[course[0]]=0;
    }
    for(auto course:courses){
        Vertice[course[0]]=vector<string>();
        for(auto compare:courses){
            if(compare==course){
                continue;
            }
            if(confliction(course,compare)){//may be need while
                Vertice[course[0]].push_back(compare[0]);
                continue;
            }
        }
    }
    for(auto i:Vertice){
        if(colors[i.first]==0){
            colors[i.first]++;
        }
        vector<string> test=Vertice[i.first];
        bool same=true;
        while(same){
            same=false;
            for(auto connect:test){
                if(colors[connect]==colors[i.first]){
                    colors[i.first]++;
                    same=true;
                    break;
                }
            }
        }
        
    }
    V2D schedule;
    for(auto time:timeslots){
        schedule.push_back(vector<string>{time});
    }
    for(auto color:colors){
        if(size_t(color.second)>timeslots.size()){
            return V2D{vector<string>{"-1"}};
        }
        schedule[color.second-1].push_back(color.first);
    }
return schedule;
}


/////
    // V2D schedule;
    // map<string,vector<string>> data;
    // for(auto course:courses){
    //     data[course[0]]=course;
    // }
    // for(auto time:timeslots){
    //     schedule.push_back(vector<string>{time});
    // }
    // for(auto course:courses){
    //     bool add=true;
    //     for(auto& time:schedule){ 
    //         add=true;
    //         if(time.size()==1){
    //             time.push_back(course[0]);
    //             break;
    //         }
    //         for(size_t j=1;j<time.size();j++){
    //             if(confliction(data[time[j]],course)){
    //                 add=false;
    //                 break;
    //             }
    //         }
    //         if(add){
    //             time.push_back(course[0]);
    //             break;
    //         }
    //     }      
    //     if(!add){
    //         schedule.clear();
    //         schedule.push_back(vector<string>{"-1"});
    //     }  
    // }
