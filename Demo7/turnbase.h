#include<iostream>
#include<string>
#include<cmath>
#include<ctime>
#include <thread>  // ใช้สำหรับ sleep_for
#include <chrono>  // ใช้สำหรับหน่วยเวลา
#include <vector>
#include<cstdlib>
#include<iomanip>
#include <algorithm> // ใช้ ตรวจสอบค่าใน array
#include <set>

using namespace std;

void Page1();
char Page2();
void createwindowCom();
void createwindowPlayer();
void Page3(char ComOrPlayer);
void createpokemon();

int comChoice();
void turnbase(int p1, int p2);
void Pageturnbase(char who);
void showpokemon();
void delaySeconds(double seconds);
void selectpokemon(char who);
void win(int p);


string namepokemon[6] = {"Arthur Morgan", "Boudica", "Caesar", "Darius", "Edward the Black Prince", "Frederick the Great"};                //ชื่อ
double hppokemon[6] = {100.0, 100.0, 150.0, 150.0, 200.0, 200.0}; 
double hpmaxpokemon[6] = {100.0, 100.0, 150.0, 150.0, 200.0, 200.0};  //รอแก้ไขให้สมดุล
double defpokemon[6] = {20.0, 20.0, 40.0, 40.0, 70.0, 70.0};        //รอแก้ไขให้สมดุล
double atkpokemon[6] = {50.0, 50.0, 30.0, 30.0, 20.0, 20.0};        //รอแก้ไขให้สมดุล
double spdpokemon[6] = {20.0, 20.0, 5.0, 5.0, 1.0, 1.0};    
string elementpokemon[4] = {"Earth", "Water", "Fire", "Wind"};
string skillinfopokemon[6] = {"<<Heal>> success rate is 1/4 recover hp equal 1/2 of maxhp.\n", 
                        "<<Piercing>> attack and strike ignore defend for 3 turn.\n", 
                        "<<Poison>> opponent take damage 10% of maxhp for 3 turn.\n", 
                        "<<Tosscoin>> you have to toss coin rate 1/2 for each turn you need to Flip heads 3 times in a row for defeat opponent.\n", 
                        "<<Sleep>> sucess rate is 1/3 opponent can't action 1 turn.\n", 
                        "<<Transfer>> sucess rate is 1/5 swap HP with the opponent.\n"};
int choices[4] = {1, 2, 3, 4}; //1 = ตีปกติ, 2 = strike, 3 = ป้องกัน, 4 = counter
int skillpokemon[6] = {1, 2, 3, 4, 5, 6};

class pokemon
{
    public:    
        string namepokemon;                //ชื่อ
        double hp;    //รอแก้ไขให้สมดุล
        double hpmax;
        double def;   //รอแก้ไขให้สมดุล
        double atk;  //รอแก้ไขให้สมดุล
        double spd;
        int skill;
        string element;
        string skillinfo;
        int consecutiveHeads = 0;
        bool sleep = false;

        friend class player;
};

class player
{
    string type;
    string name;
    vector<string> skill;
    
    public:
        vector<pokemon> myteam;
        bool checkpiercing = false;
        bool checkpoinson = false;
        int muramasa = 0;
        int poinson = 0;
        string nameplayer;                //ชื่อ
        int playerAction;
        double takeNormalATK(int n, player &opp, double winelement);
        double takeStrike(int n, player &opp, double winelement);
        void def(int n);
        void undef(int n);
        int evade();
        void createplayer(const string &n);
        void choosepokemon(int n);
        void chooseskill(int n);
        void comchoosepokemon();
        bool isDead(int n);
        void showstat(int n, int who);
        double checkspd(int n);
        void swappokemon(int n);
        void comswap(int n);
        void showPK();

        int checkelement(int n); //เช็คธาตุ
        bool checkdodge();  //เช็คหลบหลีก
        int checkskill(int n);  //เช็คskill
        
        double skill_1heal(int n); 
        int skill_2muramasa();
        int skill_3poinson();
        void skill_4tosscoin(int n, player &opp);
        void skill_5skip(int n);
        void skill_6transfer(int n, player &opp);

        double takepoinson(int n, player &opp);
};

void player::showPK(){
    for(int i = 1; i<3 ; i++){
        cout << "-------------------------" << endl;
        cout << "Name [" << i+1 << "] : " << myteam[i].namepokemon << endl; 
        cout << "HP : " << myteam[i].hp << "/" << myteam[i].hpmax << endl;
        cout << "DEF : " << myteam[i].def << endl;
        cout << "ATK : " << myteam[i].atk << endl;
        cout << "SPD : " << myteam[i].spd << endl;
        cout << "SKILL : " << myteam[i].skillinfo << endl;
        cout << "-------------------------" << endl;
        delaySeconds(0.5);
    }
}

void player::swappokemon(int n) {
    int order;
    
    //แสดงว่าใครจะเปลี่ยนตัว
    cout << endl << type << " : " << name << endl;
    //เช็คว่ากดเปลี่ยนตัวหรือโปเกม่อนตาย ถ้าตายให้แสดงว่าตาย   
    if(myteam[n].hp == 0){
        cout << "Name : " << myteam[n].namepokemon << " is dead" << endl;
    }

    while (true) { 
        showPK();
        cout << "Please select [2] or [3] : ";
        cin >> order;

        
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Invalid input! Please enter 2 or 3.\n";
            continue;
        }

       
        if (order == 2 && myteam[1].hp != 0) {
            swap(myteam[0], myteam[1]);
            cout << "-------------------------\n";
            cout << myteam[0].namepokemon << " I choose you!!!\n";
            cout << "-------------------------\n";
            break; 
        }
        else if (order == 3 && myteam[2].hp != 0) {
            swap(myteam[0], myteam[2]);
            cout << "-------------------------\n";
            cout << myteam[0].namepokemon << " I choose you!!!\n";
            cout << "-------------------------\n";
            break; 
        }
        else {
            cout << "Invalid choice! Please select a Pokemon that is still alive.\n";
        }
    }
}

//double player::skillattack(string skill){
    //if(skill == "tossCoin"){
       
   // }
//}

void player::comswap(int n){
    swap(myteam[0], myteam[n]);
}

//เพิ่ม ตัวคูณชนะธาตุ ในฟังก์ชัน takenormalatk 
double player::takeNormalATK(int n, player &opp, double winelement){
    double realoppdef = opp.myteam[n].def;

    if(checkpiercing == true){
        realoppdef = 0;
    }

    double damage = (myteam[n].atk*winelement*(1-(realoppdef/100)));
    opp.myteam[n].hp -= damage;

    return damage;
}

//เพิ่ม ตัวคูณชนะธาตุ ในฟังก์ชัน takestrike
double player::takeStrike(int n, player &opp, double winelement){
    double realoppdef = opp.myteam[n].def;

    if(checkpiercing == true){
        realoppdef = 0;
    }

    double skATK = myteam[n].atk + (abs(opp.myteam[n].spd - myteam[n].spd)*10);
	double damage = (skATK*winelement*(1-(realoppdef/100)));
    opp.myteam[n].hp -= damage;
    return damage;
}

void player::def(int n){
    myteam[n].def *= 5;
}

void player::undef(int n){
    myteam[n].def /= 5;
}

void player::choosepokemon(int n) {
    vector<int> selected;
    int input;

    for (int i = 0; i < 3; i++) {
        while (true) {
            cout << "Please select Player " << n << "'s Pokemon ["<<i+1<<"] : ";
            cin >> input;

            if (cin.fail()) {
                cin.clear(); // เคลียร์สถานะผิดพลาดของ cin
                cin.ignore(1000, '\n'); // ลบค่าในบัฟเฟอร์ ป้องกันลูปไม่มีที่สิ้นสุด
                cout << "Invalid input! please select again.\n";
                continue;
            }


            if (input < 1 || input > 6) {
                cout << "Invalid choice!\n";
                continue;
            }

            if (find(selected.begin(), selected.end(), input) != selected.end()) {
                cout << "Already selected, please select again.\n";
            } else {
                selected.push_back(input);
                break;
            }
        }

        pokemon unit;
        unit.namepokemon = namepokemon[input - 1];
        unit.atk = atkpokemon[input - 1];
        unit.hp = hppokemon[input - 1];
        unit.hpmax = hpmaxpokemon[input - 1];
        unit.def = defpokemon[input - 1];
        unit.spd = spdpokemon[input - 1];
        unit.element = elementpokemon[rand() % 4];
        unit.skillinfo = skillinfopokemon[input - 1];
        unit.skill = skillpokemon[input - 1];

        myteam.push_back(unit);
    }
}

void player::createplayer(const string &n) {
    if(n == "Player 2" || n == "Player 1"){
        cout << n << " : " << "PLEASE ENTER YOUR NAME : ";
        cin.ignore();
        getline(cin, name);
    }
    else{
        name = "AI";
    }
    type = n;
}


int player::evade(){
    int rate = rand()%100 + 1;
	return rate;
}


void player::comchoosepokemon() {
    set<int> selectedIndices; // ใช้ set ป้องกันค่าซ้ำ
    srand(time(0)); // ตั้งค่า seed สำหรับ rand()

    cout << "Computer is selecting Pokemon...\n";
    while (selectedIndices.size() < 3) {
        int randIndex = rand() % 6; // สุ่มค่า 0-5
        if (selectedIndices.insert(randIndex).second) { // ถ้าค่าไม่ซ้ำ ให้เพิ่ม
            pokemon unit;
            unit.namepokemon = namepokemon[randIndex];
            unit.atk = atkpokemon[randIndex];
            unit.hp = hppokemon[randIndex];
            unit.hpmax = hpmaxpokemon[randIndex];
            unit.def = defpokemon[randIndex];
            unit.spd = spdpokemon[randIndex];
            unit.element = elementpokemon[rand() % 4];
            unit.skillinfo = skillinfopokemon[randIndex];
            unit.skill = skillpokemon[randIndex];

            myteam.push_back(unit);
            cout << "Selected: " << unit.namepokemon << "\n";
        }
    }
}

bool player::isDead(int n){
    if(myteam[n].hp <= 0){
        myteam[n].hp = 0;
        return true;
    }
    else return false;
}

void player::showstat(int n, int who){
    if(who == 1){
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "Player 1's name : " << name << endl;
        cout << "Pokemon name : " << myteam[n].namepokemon << "\tElement : " << myteam[n].element << endl;
        cout << "HP : " << myteam[n].hp << "/" << myteam[n].hpmax << "\tATK : "<< myteam[n].atk << "\tDEF : "<< myteam[n].def << endl;
        cout << "SKILL : "  << myteam[n].skillinfo << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
    }
    else{
        cout << "\t\t\t\t\t\t---------------------------------------------------------------------------------" << endl; 
		cout << "\t\t\t\t\t\tPlayer 2's name : " << name << endl; 
		cout << "\t\t\t\t\t\tPokemon name : " << myteam[n].namepokemon << "\tElement : " << myteam[n].element << endl;
        cout << "\t\t\t\t\t\tHP : " << myteam[n].hp << "/" << myteam[n].hpmax << "\tATK : "<< myteam[n].atk << "\tDEF : "<< myteam[n].def << endl;
		cout << "\t\t\t\t\t\tSKILL : "  << myteam[n].skillinfo << endl;
        cout << "\t\t\t\t\t\t---------------------------------------------------------------------------------" << endl;
    }
}

double player::checkspd(int n){
    return myteam[n].spd;
}

//สร้างฟังก์ชันเช็ค ธาตุ
int player::checkelement(int n)
{
    string strele = myteam[n].element;
    for(int i = 0; i < myteam[n].element.size(); i++){
        strele[i] = tolower(myteam[n].element[i]);
    }
    int ele = 0;
    if(strele == "earth") ele = 1;
    if(strele == "water") ele = 2;
    if(strele == "fire") ele = 3;
    if(strele == "wind") ele = 4;
    return ele;
}

//หลบหลีก 12.5%
bool player::checkdodge(){
    int random = rand() % 8;
    if(random == 0){
        return true;
    }
    return false;
}

//เช็ค skill ว่าเป็นของตัวอะไร
int player::checkskill(int n){
    return myteam[n].skill;
}

//skill heal 0.5 hpmax โอกาส 1/4 
double player::skill_1heal(int n){
    double heal = 0.5 * myteam[n].hpmax;
    int randomchance = (rand() * 77) % 4;
    if(randomchance == 0){

        if(heal + myteam[n].hp > myteam[n].hpmax){
            heal = myteam[n].hpmax - myteam[n].hp;
        }
        myteam[n].hp += heal;
        return heal;
    }
    else return 0.0;  
}

//เริ่ม ใช้ skill2 defend = 0
int player::skill_2muramasa(){
    muramasa = 1;
    checkpiercing = true;
    return muramasa;
}

//เริ่ม ใช้ skill3 ติดพิษ
int player::skill_3poinson(){
    poinson = 1;
    checkpoinson = true;
    return poinson; 
}

//ทำติดพิษ
double player::takepoinson(int n, player &opp){
    double poinsononhp = 0.15 * opp.myteam[n].hpmax;
    opp.myteam[n].hp -= poinsononhp;
    return poinsononhp;
}

//skill4 สุ่มหัวก้อย ถ้าหัวครบ 3 บังคับฝ่ายตรงข้ามแพ้ 1 ตัว
void player::skill_4tosscoin(int n, player &opp){
    int flip = rand() % 2;
    if(flip == 1){
        cout << " Coin is Head ";
        myteam[n].consecutiveHeads++;
    }
    else{
        myteam[n].consecutiveHeads = 0;
        cout << " Coin is tails";
        cout << " Reset....";
    }
    cout << " Death count : " << myteam[n].consecutiveHeads;
    if(myteam[n].consecutiveHeads == 3){
        opp.myteam[n].hp = 0;
        myteam[n].consecutiveHeads = 0;
        cout << " You died!!!!!! ";
    }
}

//skill5 ข้ามเทิร์น
void player::skill_5skip(int n){
    int sucess = rand() % 4;
    if(sucess == 3){
        myteam[n].sleep = true;
        cout << " Sucess!!!!!";
    }
    else{
        cout << " Fail!!!!!";
    }
}

//skill6 สลับเลือดกับฝั่งตรงข้าม
void player::skill_6transfer(int n, player &opp){
    int sucess = rand() % 5;

    if(sucess == 1){
        double temp = myteam[n].hp;
        myteam[n].hp = opp.myteam[n].hp;
        opp.myteam[n].hp = temp;
        cout << " Sucess!!!!!";
    }
    else{
        cout << " Fail!!!!!";
    }

    if(myteam[n].hp > myteam[n].hpmax) myteam[n].hp = myteam[n].hpmax;
    if(opp.myteam[n].hp > opp.myteam[n].hpmax) opp.myteam[n].hp = opp.myteam[n].hpmax;
}

//เพิ่ม ตัวคูณชนะธาตุ ในฟังก์ชัน takenormalatk takestrike
//เพิ่ม การเช็คการหลบหลีก
void drawscene(int p1, player &p_1, int p2, player &p_2){
    bool checkdef1 = false;
    bool checkdef2 = false;
    int elementplayer1 = p_1.checkelement(0);
    int elementplayer2 = p_2.checkelement(0);

    double winelement1 = 1.0;
    double winelement2 = 1.0;

    bool dodge1 = p_1.checkdodge();
    bool dodge2 = p_2.checkdodge();

    if(elementplayer1 == 1){
        if(elementplayer2 == 2){
            winelement1 = 1.5;
        }
        if(elementplayer2 == 4){
            winelement2 = 1.5;
        }
    }
    if(elementplayer1 == 2){
        if(elementplayer2 == 3){
            winelement1 = 1.5;
        }
        if(elementplayer2 == 1){
            winelement2 = 1.5;
        }
    }
    if(elementplayer1 == 3){
        if(elementplayer2 == 4){
            winelement1 = 1.5;
        }
        if(elementplayer2 == 2){
            winelement2 = 1.5;
        }
    }
    if(elementplayer1 == 4){
        if(elementplayer2 == 1){
            winelement1 = 1.5;
        }
        if(elementplayer2 == 3){
            winelement2 = 1.5;
        }
    }
    
    if(p1 == 1){
        cout << "Player 1 Attack!!!!!";
        if(!dodge2){
            double damage = p_1.takeNormalATK(0, p_2, winelement1);
            cout << " " << setw(2) << damage << " Damage";
        }
        else{
            cout << " " << "Miss!!!!!";
        }
    }
    if(p1 == 2){
        cout << "Player 1 Strike!!!!!";
        if(!dodge2){
            if(p2 != 4){
                double damage = p_1.takeStrike(0, p_2, winelement1);
                cout << setw(2) << " " << damage << " Damage";
            }
        }
        else{
            cout << " " << "Miss!!!!!";
        }
    }
    if(p1 == 3){
        cout << "Player 1 Defend!!!!!";
        if(p2 != 2){
            p_1.def(0);
            checkdef1 = true;
        }
    }
    if(p1 == 4){
        cout << "Player 1 Counter!!!!!";
        if(p2 == 2){
            double damage = p_1.takeStrike(0, p_2, winelement1);
            cout << " " << setw(2) << damage << " Damage";
        }
    }
    // เพิ่มกรณี กดskill
    if(p1 == 5){
        int skill1 = p_1.checkskill(0);
        cout << "Player 1 Skill!!!!!";
        if(skill1 == 1){
            double heal = p_1.skill_1heal(0);
            cout << " Heal!!!!!";
            if(heal == 0.0){
                cout << " Fail!!!!!";
            }
            else{
                cout << setw(2) << " +" << heal;
            }
        }
        if(skill1 == 2){
            p_1.muramasa = p_1.skill_2muramasa();
            cout << " Piercing!!!!!";
            goto p1_jumpskill2;
        }
        if(skill1 == 3){
            p_1.poinson = p_1.skill_3poinson();
            cout << " Poinsoned!!!!!";
            goto p1_jumpskill3;
        }
        if(skill1 == 4){
            cout << " TossCoin!!!!!";
            p_1.skill_4tosscoin(0, p_2);
        }
        if(skill1 == 5){
            cout << " Sleep!!!!!";
            p_2.skill_5skip(0);
        }
        if(skill1 == 6){
            cout << " Transfer!!!!!";
            p_1.skill_6transfer(0, p_2);
        }
    }
    if(p1 == 6){
        p_1.swappokemon(0);
    }
    //เช็กว่าติดพิษอยู่มั้ย 
    if(p_1.checkpoinson == true && p_1.poinson <= 3){
        double damage = p_1.takepoinson(0, p_2);
        cout << " +Poinson " << damage << " Damage " << p_1.poinson << "/3" ;
        p_1.poinson++;
    }
    else{
        p_1.checkpoinson = false;
        p_1.poinson = 0;
    }

    //เช็กว่าสกิล 2 ตีไม่สน def ยังติดอยู่มั้ย
    if(p_1.checkpiercing == true && p_1.muramasa <= 3){
        cout << " " << p_1.muramasa << "/3" ;
        p_1.muramasa++;
    }
    else{
        p_1.checkpiercing = false;
        p_1.muramasa = 0;
    }

    p1_jumpskill2:
    p1_jumpskill3:

    if(p2 == 1){
        cout << "\t\t\t\tPlayer 2 Attack!!!!!";
        if(!dodge1){
            double damage = p_2.takeNormalATK(0, p_1, winelement2);
            cout << " " << setw(2) << damage << " Damage";
        }
        else{
            cout << " " << "Miss!!!!!";
        }
    }
    if(p2 == 2){
        cout << "\t\t\t\tPlayer 2 Strike!!!!!";
        if(!dodge1){
            if(p1 != 4){
                double damage = p_2.takeStrike(0, p_1, winelement2);
                cout << " " << setw(2) << damage << " Damage";
            }
        }
        else{
            cout << " " << "Miss!!!!!";
        }
    }
    if(p2 == 3){
        cout << "\t\t\t\tPlayer 2 Defend!!!!!";
        if(p1 != 2){
            p_2.def(0);
            checkdef2 = true;
        }
    }
    if(p2 == 4){
        cout << "\t\t\t\tPlayer 2 Counter!!!!!";
        if(p1 == 2){
            double damage = p_2.takeStrike(0, p_1, elementplayer2);
            cout << " " << setw(2) << damage << " Damage";
        }
    }
    // เพิ่มกรณี กดskill
    if(p2 == 5){
        int skill2 = p_2.checkskill(0);
        cout << "\t\t\t\tPlayer 2 Skill!!!!!";
        if(skill2 == 1){
            double heal = p_2.skill_1heal(0);
            if(heal == 0.0){
                cout << " " << "Fail!!!!!";
            }
            else{
                cout << " " << setw(2) << "Heal +" << heal;
            }
        }
        if(skill2 == 2){
            p_2.muramasa = p_2.skill_2muramasa();
            cout << " " << "Piercing!!!!!";
            goto p2_jumpskill2;
        }
        if(skill2 == 3){
            p_2.poinson = p_2.skill_3poinson();
            cout << " " << "Poinsoned!!!!!";
            goto p2_jumpskill3;
        }
        if(skill2 == 4){
            cout << " " << "TossCoin!!!!!";
            p_2.skill_4tosscoin(0, p_1);
        }
        if(skill2 == 5){
            cout << " " << "Sleep!!!!!";
            p_1.skill_5skip(0);
        }
        if(skill2 == 6){
            cout << " " << "Transfer!!!!!";
            p_2.skill_6transfer(0, p_1);
        }
    }
    if(p2 == 6){
        p_2.swappokemon(0);
    }
    //เช็กว่าติดพิษอยู่มั้ย 
    if(p_2.checkpoinson == true && p_2.poinson <= 3){
        double damage = p_2.takepoinson(0, p_1);
        cout << " +Poinson " << damage << " Damage " << p_2.poinson << "/3" ;
        p_2.poinson++;
    }
    else{
        p_2.checkpoinson = false;
        p_2.poinson = 0;
    }
    //เช็กว่าสกิล 2 ตีไม่สน def ยังติดอยู่มั้ย
    if(p_2.checkpiercing == true && p_2.muramasa <= 3){
        cout << " " << p_2.muramasa << "/3" ;
        p_2.muramasa++;
    }

    else{
        p_2.checkpiercing = false;
        p_2.muramasa = 0;
    }

    p2_jumpskill2:
    p2_jumpskill3:

    if(checkdef1){
        p_1.undef(0);
    }
    if(checkdef2){
        p_2.undef(0);
    }

    cout << endl;
}

void win(int p){
    cout << "===========================================================================" << endl;
    for(int i = 0; i < 3; i++) cout << endl;
    cout << "                                      Player" << p << "Win" << endl;
    for(int i = 0; i < 3; i++) cout << endl;
    cout << "===========================================================================" << endl;
}


bool sc;


void delaySeconds(double seconds) {
    clock_t start_time = clock();
    while ((clock() - start_time) / (double)CLOCKS_PER_SEC < seconds);
}

void Page1(){
    string entertocontinue;
    cout << "----------------------------------" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "|          pokemonkings          |" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "----------------------------------" << endl;
    cout << "     Please Enter to continue     " << endl;
    getline(cin, entertocontinue);
}

char Page2(){
    char who;

        cout << "----------------------------------------" << endl;
        cout << "(1) Play with Computer (PVE) : Type (C)" << endl;
        cout << "(2) Play with Player   (PVP) : Type (P)" << endl;
    
    do{
        cout << "Enter your answer : ";
        cin >> who;
    }while(toupper(who) != 'C' && toupper(who) != 'P');

    if(toupper(who) == 'C'){
        cout << ">>> (1) Play with Computer (PVE) <<<" << endl;
    }    
    else{
        cout << ">>> (2)  Play with Player  (PVP) <<<" << endl;
    }

    cout << "----------------------------------------" << endl;

    cin.ignore();
    return who;
}

void Return2Menu() {
    string entertoreturn;
    cout << "----------------------------------" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "|         return to menu         |" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "----------------------------------" << endl;
    cout << "     Please press Enter to continue     " << endl;
    
    cin.sync();  
    cin.ignore(); 
    getline(cin, entertoreturn);
}


int randomnumber(int n){        //ฟังชั่นสุ่ม
    return ((rand() % 100) * 77) % n;
}


int comChoice()
{
	int choices[] = {1, 2, 3, 4};
	return choices[rand()%4];
}

void showpokemon(){
    string input;
    for(int i = 0; i < 6; i++){
        cout << "-------------------------" << endl;
        cout << "NAME [" << i+1 << "] : " << namepokemon[i] << endl; 
        cout << "HP : " << hppokemon[i] << endl;
        cout << "DEF : " << defpokemon[i] << endl;
        cout << "ATK : " << atkpokemon[i] << endl;
        cout << "SPD : " << spdpokemon[i] << endl;
        cout << "SKILL : " << skillinfopokemon[i] << endl;
        cout << "-------------------------" << endl;
        delaySeconds(0.5);
        if(i != 5){
            cout << ">>> Please Enter to see more <<<" << endl;
            getline(cin, input);
        }
    }
}
