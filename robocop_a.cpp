#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

//#define DEBUG

using namespace std;

void idx_finder(int& a, int& b, vector<int> ans_, int target){
    int temp_len=0,x;
    for (x=0;x<ans_.size()-1;x++){

        if (temp_len < target && target <= temp_len+ans_[x]){
            break;
        }
        temp_len += ans_[x];
    }
    if (x%2 ==0){
        a = x/2;
        b = x/2;
    }
    else {
        a = x/2+1;
        b = x/2;
    }
}

int main()
{

    int num_of_vertex;
    cin >> num_of_vertex;

    int x,y;
    vector<int> vec_x,vec_y;
    int x_start=0,y_start=0;
    for (int i=0;i<num_of_vertex;i++){
        cin >> x >>y;
        if (vec_x.end()==find(vec_x.begin(),vec_x.end(),x))vec_x.push_back(x);
        if (vec_y.end()==find(vec_y.begin(),vec_y.end(),y))vec_y.push_back(y);
        if (i==1 && vec_x.size()==2){
            x_start = 1;
        }
        else if (i==1 && vec_y.size()==2){
            y_start = 1;
        }
    }

//    #ifdef DEBUG
//        cout << "\n\nvector\n\n" <<endl;
//        for (auto x:vec_x) cout << x << "\n";
//        cout << "\n\n";
//        for (auto y:vec_y) cout << y << "\n";
//    #endif // DEBUG


    vector<int>len_x,len_y;
    for (int idx=0;idx<vec_x.size()-1;idx++){
        len_x.push_back(vec_x[idx+1]-vec_x[idx]);
        len_y.push_back(vec_y[idx+1]-vec_y[idx]);
    }


    len_x.push_back(vec_x.back()-vec_x.front());
    len_y.push_back(vec_y.back()-vec_y.front());


//    #ifdef DEBUG
//        cout << "\n\nlen_vector\n\n" <<endl;
//        for (auto x:len_x) cout << x << "\n";
//        cout << "\n\n";
//        for (auto y:len_y) cout << y << "\n";
//    #endif // DEBUG


    int abs_len=0;
    for (auto x:len_x) abs_len+=abs(x);
    for (auto y:len_y) abs_len+=abs(y);


//    #ifdef DEBUG
//        cout << abs_len<<endl;
//    #endif


    vector<int> ans;
    if (vec_x[0]==vec_x[1]){
        for (int i=0;i<len_x.size();i++){
            ans.push_back(abs(len_y[i]));
            ans.push_back(abs(len_x[i]));
        }
    }
    else {
        for (int i=0;i<len_x.size();i++){
            ans.push_back(abs(len_x[i]));
            ans.push_back(abs(len_y[i]));
        }
    }

    string sentence,word;
    int num;
    vector<int> target_num;
    cin.ignore();
    getline(cin,sentence);
    istringstream iss (sentence);

    while (iss >> word){
        num = stoi(word);
        num %= abs_len;
        target_num.push_back(num);
//        #ifdef DEBUG
//            cout << "target_num : " << num << endl;
//        #endif
    }

    int idx_x,idx_y;
    for (auto i:target_num){
            int abs_pass_len=0,extra_len=0;
        if (x_start){
            idx_finder(idx_x,idx_y,ans,i);
//        #ifdef DEBUG
//            cout <<"\n index"<<endl;
//            cout << idx_x << "  " << idx_y <<endl;
//        #endif

        }
        else {
            idx_finder(idx_y,idx_x,ans,i);
//        #ifdef DEBUG
//            cout <<"\n index"<<endl;
//            cout << idx_x << "  " << idx_y <<endl;
//        #endif
        }
        int ans_x=vec_x.front(), ans_y = vec_y.front();
        for (int j=0;j<idx_x;j++){
                ans_x+=len_x[j];
                abs_pass_len+=abs(len_x[j]);
            }
        for (int h=0;h<idx_y;h++){
                ans_y+=len_y[h];
                abs_pass_len+=abs(len_y[h]);
            }
//        #ifdef DEBUG
//            cout << "answer" <<endl;
//            cout << ans_x << " " << ans_y<<"\n" <<endl;
//        #endif

        extra_len = i-abs_pass_len;
//        #ifdef DEBUG
//            cout << "extra len : " << extra_len << endl;
//        #endif

        if (idx_x==idx_y){
            ans_x += x_start*extra_len*(len_x[idx_x]/abs(len_x[idx_x]));
            ans_y += y_start*extra_len*(len_y[idx_y]/abs(len_y[idx_y]));
        }
        else {
            ans_x += y_start*extra_len*(len_x[idx_x]/abs(len_x[idx_x]));
            ans_y += x_start*extra_len*(len_y[idx_y]/abs(len_y[idx_y]));
        }
        cout <<ans_x << " " <<ans_y<<endl;
    }


    return 0;
}
