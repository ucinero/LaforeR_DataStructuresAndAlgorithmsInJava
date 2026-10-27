// project_6_5.cpp

#include <iostream>
using namespace std;

void showTeams(int group, int team, int index, string current_team) {
    if (index > 26 || group < team)
        return;
    if (team == 0) {
        cout << current_team << endl;
        return;
    }
    char ch = 'A' + index;
    string next_team = current_team + ch;
    showTeams(group - 1, team - 1, index + 1, next_team);
    showTeams(group - 1, team, index + 1, current_team);

}


int main() {
    string temp_string = "";
    int indx = 0;

    int group = 6;
    int team = 4;
    showTeams(group, team, indx, temp_string);

    return 0;
}