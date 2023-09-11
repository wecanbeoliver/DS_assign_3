#include <iostream>
#include <vector>
#include <algorithm>
//#define SKIP cout << "\n\n"

//#define DEBUG

using namespace std;


int neg_or_pos(int x) {
    return (x>0) ? 1 : -1;
}

int main() {

    int num_of_vertex;
    cin >> num_of_vertex;

    int x,y;
    vector<int> vec_x,vec_y;
    int x_start=0,y_start=0;
    for (int i=0; i<num_of_vertex; i++) {
        cin >> x >> y;
        vec_x.push_back(x);
        vec_y.push_back(y);
    }

    if (vec_x[0]==vec_x[1]) y_start=1;
    else x_start=1;




    vector<int> ans; // length vector


    for (int i=0;i<vec_x.size()-1;i++){
        if (vec_x[i]==vec_x[i+1]) ans.push_back(vec_y[i+1]-vec_y[i]);
        else ans.push_back(vec_x[i+1]-vec_x[i]);
    }


    if (x_start) ans.push_back(vec_y.front()-vec_y.back());
    else ans.push_back(vec_x.front()-vec_x.back());


//    #ifdef DEBUG
//        cout << "\n\n ans_vector\n\n" <<endl;
//        for (auto x:ans) cout << x << "\n";
//    #endif // DEBUG


    int abs_len=0;
    for (auto i:ans) abs_len+=abs(i);


//    SKIP;
//    for (auto x:ans) cout<<  x << endl;


    int target_num;

    while (cin >> target_num) {

        target_num %= abs_len;
        int ans_x=vec_x.front(), ans_y=vec_y.front(); //starting point
        int abs_pass_len=0, extra_len=0;


        int temp1=0,temp2=0,i;
        for (i=0;ans.size();i++){
            abs_pass_len+=abs(ans[i]);


            if (abs_pass_len > target_num){
                abs_pass_len-=abs(ans[i]);
                break;
            }

            if (i%2==0) temp1+=ans[i];
            else temp2+=ans[i];

            if (abs_pass_len == target_num){
                break;
            }


        }

        extra_len = target_num-abs_pass_len;



        ans_x+= temp1*x_start+temp2*y_start;
        ans_y+= temp2*x_start+temp1*y_start;

        if (i%2==0){
            if (x_start) ans_x+=neg_or_pos(ans[i])*extra_len;
            else ans_y+=neg_or_pos(ans[i])*extra_len;
        }

        else {
            if (x_start) ans_y+=neg_or_pos(ans[i])*extra_len;
            else ans_x+=neg_or_pos(ans[i])*extra_len;
        }


        cout <<ans_x<< " " <<ans_y<<endl;

    }


    return 0;
}
