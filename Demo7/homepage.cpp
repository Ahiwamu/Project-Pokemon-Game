#include "turnbase.h"

int main()
{
    while(true){
	    srand(time(0)); 
        Page1();
        char who = Page2();
      

        player p1, p2;
      
        p1.createplayer("Player 1");
        showpokemon();
        p1.choosepokemon(1);
        delaySeconds(0.5);

        if(toupper(who) == 'C'){
            int dead = 0;
            p2.createplayer("Computer");
            p2.comchoosepokemon();
            while(true)
            {
           
                
                while(true){
                    delaySeconds(1);
                    p1.showstat(0, 1);
                    p2.showstat(0, 2);

                    
                    if(p1.myteam[0].sleep == true){
                        cout << "Player 1 can do nothing....." << endl;
                        p1.playerAction = 0;
                        p1.myteam[0].sleep = false;
                        break;
                    }
                    cout << "[1] Attack [2] Strike [3] Defend [4] counter [5] skill [6] swap" << endl;
                    cout << "Player'1 Choice : ";
                    cin >> p1.playerAction;
                    if (cin.fail() || p1.playerAction < 1 || p1.playerAction > 6) {
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "Invalid input. Please choose again." << endl;
                    } else {
                        break;
                    }
                
                }
                int action1 = p1.playerAction;
                delaySeconds(0.5);

                while(true){
                    
                    if(p2.myteam[0].sleep == true){
                        cout << "Computer can do nothing....." << endl;
                        p2.playerAction = 0;
                        p2.myteam[0].sleep = false;
                        break;
                    }
                    
                    p2.playerAction = randomnumber(4) + 1;
                    cout << "Computer Choice : " << p2.playerAction << endl;
                    break;
                    
                }
                
                int action2 = p2.playerAction;
                cout << "===========================================================================================================" << endl;
                drawscene(action1, p1, action2, p2);
                cout << "===========================================================================================================" << endl;
                cout << endl;
               
                if(p2.isDead(0)){
                    dead += 1;
                }

                delaySeconds(1);
                if(p1.isDead(0) && p2.isDead(0)){
                    if(p1.checkspd(0) < p2.checkspd(0)){
                        if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2)){
                            win(2);
                            break;
                        }else{
                            p1.swappokemon(0);
                            p2.comswap(dead);
                        }
                    }
                    else if(p1.checkspd(0) > p2.checkspd(0)){
                        if(p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                            win(1);
                            break;
                        }else{
                            p1.swappokemon(0);
                            p2.comswap(dead);
                        }
                    }else if(p1.checkspd(0) == p2.checkspd(0)){
                        if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2) && p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                            cout << "===========================================================================" << endl;
                            for(int i = 0; i < 3; i++) cout << endl;
                            cout << "                                      draw" << endl;
                            for(int i = 0; i < 3; i++) cout << endl;
                            cout << "===========================================================================" << endl;
                            break;
                        }else if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2)){
                            win(2);
                            break;
                        }else if (p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                            win(1);
                            break;
                        }else{
                            p1.swappokemon(0);
                            p2.comswap(dead);
                        }
                }
                }
                else if(p2.isDead(0)){
                    if(p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                        win(1);
                        break;
                    }else p2.comswap(dead);
                    
                }
                else if(p1.isDead(0)){
                    if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2)){
                        win(2);
                        break;
                    }else p1.swappokemon(0);
                }   
            
        }
            delaySeconds(2);
            Return2Menu();
        
        }else if(toupper(who) == 'P'){
            p2.createplayer("Player 2");
            showpokemon();
            p2.choosepokemon(2);

           
            while(true){
                delaySeconds(1);
                p1.showstat(0, 1);
                p2.showstat(0, 2);

                cout << "===========================================================================" << endl;
                for(int i = 0; i < 3; i++) cout << endl;
                cout << "                                 player1'sturn" << endl;
                for(int i = 0; i < 3; i++) cout << endl;
                cout << "===========================================================================" << endl;
                
                while(true){
                    if(p1.myteam[0].sleep == true){
                        cout << "Player 1 can do nothing....." << endl;
                        p1.playerAction = 0;
                        p1.myteam[0].sleep = false;
                        break;
                    }
                    else{
                        cout << "[1] Attack [2] Strike [3] Defend [4] counter [5] skill [6] swap" << endl;
                        cout << "Player'1 Choice : ";
                        cin >> p1.playerAction;
                        if (cin.fail() || p1.playerAction < 1 || p1.playerAction > 6) {
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            cout << "Invalid input. Please choose again." << endl;
                        } 
                        else break;
                    }

                }

                int action1 = p1.playerAction;
                
                cout << "===========================================================================" << endl;
                for(int i = 0; i < 3; i++) cout << endl;
                cout << "                                 player2'turn" << endl;
                for(int i = 0; i < 3; i++) cout << endl;
                cout << "===========================================================================" << endl;

                while(true){
                    if(p2.myteam[0].sleep == true){
                        cout << "Player 2 can do nothing....." << endl;
                        p2.playerAction = 0;
                        p2.myteam[0].sleep = false;
                        break;
                    }
                    else{
                        cout << "[1] Attack [2] Strike [3] Defend [4] counter [5] skill [6] swap" << endl;
                        cout << "Player'2 Choice : ";
                        cin >> p2.playerAction;
                        if (cin.fail() || p2.playerAction < 1 || p2.playerAction > 6) {
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            cout << "Invalid input. Please choose again." << endl;
                        } 
                        else break;
                    }

                }

                int action2 = p2.playerAction;
                
                cout << "===========================================================================================================" << endl;
                drawscene(action1, p1, action2, p2);
                cout << "===========================================================================================================" << endl;
                cout << endl;
                
                delaySeconds(1);
                if(p1.isDead(0) && p2.isDead(0)){
                    if(p1.checkspd(0) < p2.checkspd(0)){
                        if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2)){
                            win(2);
                            break;
                        }else{
                            p1.swappokemon(0);
                            p2.swappokemon(0);
                        }
                    }
                    else if(p1.checkspd(0) > p2.checkspd(0)){
                        if(p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                            win(1);
                            break;
                        }else{
                            p1.swappokemon(0);
                            p2.swappokemon(0);
                        }
                    }else if(p1.checkspd(0) == p2.checkspd(0)){
                        if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2) && p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                            cout << "===========================================================================" << endl;
                            for(int i = 0; i < 3; i++) cout << endl;
                            cout << "                                      draw" << endl;
                            for(int i = 0; i < 3; i++) cout << endl;
                            cout << "===========================================================================" << endl;
                            break;
                        }else if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2)){
                            win(2);
                            break;
                        }else if (p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                            win(1);
                            break;
                        }else{
                            p1.swappokemon(0);
                            p2.swappokemon(0);
                        }
                }
                }
                else if(p2.isDead(0)){
                    if(p2.isDead(0) && p2.isDead(1) && p2.isDead(2)){
                        win(1);
                        break;
                    }else p2.swappokemon(0);
                    
                }
                else if(p1.isDead(0)){
                    if(p1.isDead(0) && p1.isDead(1) && p1.isDead(2)){
                        win(2);
                        break;
                    }else p1.swappokemon(0);
                }
            }
            delaySeconds(2);
            Return2Menu();
        }
    };
    
    return 0;
}