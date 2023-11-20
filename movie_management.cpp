#include<bits/stdc++.h>
#include <typeinfo>
using namespace std;


vector<string> split(const string& str, char delim) 
{
    vector<string> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != string::npos) 
    {
        end = str.find(delim, start);
        strings.push_back(str.substr(start, end - start));
    }
    return strings;
}


class Audi {

    public:
    string audi_name;

    Audi(string name, vector<string> seat_list)
    {

        audi_name = name;
        for(int i=0;i<seat_list.size();i++){
            seats.insert({seat_list[i],false});
        }
    }

    int get_revenue() {return audi_revenue;}


    void show_seats(){
        cout<<"all available seats "<<audi_name<<":"<<endl;
        char c = 'a';
        for(auto it: seats){
            if(it.second == false){
                if(it.first[0]!=c){
                    cout<<endl;
                    c = it.first[0];
                }
                cout<<it.first<<" ";

            }
        }
        cout<<endl;
    }

    void book_seat(int show_number, string seat_numbers)
    {
        vector<string> seats_list = split(seat_numbers, ',');

        int flag = true;
        for(int i=0;i<seats_list.size();i++){
            string seat_number = seats_list[i];

            if(seats.count(seat_number)==0){
                cout<<"Print: "<<seat_number<<" does not exist"<<endl;
                break;
            }
           
            if(seats[seat_number]){
                //error messages
                cout<<"Print : "<<seat_number<<" not available,Please select another seat "<<endl;
                flag = false;
            }
        }
        if(!flag) return;
        int base = 0;

        for(int i=0;i<seats_list.size();i++){
            //booking and calculation
            string seat_number = seats_list[i];
            seats[seat_number] = true;

            if(seat_number[0]=='a') {base+=320;}
            else if(seat_number[0]=='b') {base+=280;}
            else if(seat_number[0]=='c') {base+=240;}

        }

        //calculate service tax and other taxes on base amount
        // Service Tax @14%: Rs. 78.40
        // Swachh Bharat Cess @0.5%: Rs. 2.80
        // Krishi Kalyan Cess @0.5%: Rs. 2.80

        float service_tax=(float)(0.14*base);
        float Swachh_bahrat_cess=(float)(0.005*base);
        float krishi_kalyan_cess=(float)(0.005*base);


        //print success message and amounts
        cout<<"Print : successfully booked - Show "<<show_number<<endl;;
        cout<<"Subtotal: Rs. "<<base<<endl;
        cout<<"Service Tax @14%: Rs."<< service_tax<<endl;
        cout<<"Swachh Bharat Cess @0.5%: Rs."<<Swachh_bahrat_cess<<endl;
        cout<<"Krishi Kalyan Cess @0.5%:"<< krishi_kalyan_cess<<endl;


        //add total amount to audi_revenue

        audi_revenue+=base;

        return;

    }
    private:
    
    map<string, bool> seats;
    int audi_revenue = 0;

};

class Theatre
{
    
    
    public:

        void create_audi(string audi_name, vector<string> audi_seats){
            Audi a(audi_name,audi_seats);
            // audi_map.insert({audi_name, a});
            audi_list.push_back(a);
        }



        void book_ticket(int show_number, string seat_number){

            if(show_number<audi_list.size()){
                audi_list[show_number-1].book_seat(show_number, seat_number);
            } else {
                cout<<"NO AUDI FOUND"<<endl;
            }

        }

        void show_audis(){
            for(int i=0;i<audi_list.size();i++){
                audi_list[i].show_seats();
            }
        }

        void total_revenue(){
            int total = 0;

            for(int i=0;i<audi_list.size();i++){
                total += audi_list[i].get_revenue();
            }


            // print total and taxes and total

            float service=(float)(0.14*total);
             float Swachh_bahrat=(float)(0.005*total);
            float krishi_kalyan=(float)(0.005*total);

            cout<<"Total Sales:"<<endl;
            cout<<"Revenue: Rs."<<total<<endl;
            cout<<"Service Tax: Rs."<<service<<endl;
            cout<<"Swachh Bharat Cess: Rs."<<Swachh_bahrat<<endl;
            cout<<"Krishi Kalyan Cess: Rs."<<krishi_kalyan<<endl;

        }

    private:
        vector<Audi> audi_list;
};

int main()
{
    Theatre th;
    // Audi a({"aniket","rawat"});

    th.create_audi("audi1", {
            "a1","a2","a3","a4","a5","a6","a7","a8","a9",
            "b1","b2","b3","b4","b5","b6",
            "c2","c3","c4","c5","c6","c7"
        });
    th.create_audi("audi2", {
            "a1","a2","a3","a4","a5","a6","a7","a8","a9",
            "b1","b2","b3","b4","b5","b6",
            "c2","c3","c4","c5","c6","c7"
        });
    th.create_audi("audi3", {
            "a1","a2","a3","a4","a5","a6","a7","a8","a9",
            "b1","b2","b3","b4","b5","b6",
            "c2","c3","c4","c5","c6","c7"
        });

    // th.show_audis();

    // th.book_ticket(1,"a1,a2,a3");
    // // th.book_ticket(2,"a1,a2,d3");

    // th.total_revenue();

    while(1)
    {
        cout<<"------------------------------------------------"<<endl;
        th.show_audis();
        cout<<"------------------------------------------------"<<endl;
        cout<<"Enter shows no : ";
        int show_no;
        cin>>show_no;
        cout<<"Enter seats ";
        string seat_number;
        cin>>seat_number;
        cout<<"------------------------------------------------"<<endl;
        th.book_ticket(show_no, seat_number);
        cout<<"------------------------------------------------"<<endl;
        th.total_revenue();
    

    }
    return 0;
}