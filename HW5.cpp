#include <iostream>
#include <string>
using namespace std;

class node{
public:
int getOn;
int getOff;
node* next;
node* prev;
};
class elevator{
public:
int floorNumber;
bool direction;
int nextFloor;
node* head;
node* tail;
elevator(){
head=NULL;
tail=NULL;
floorNumber=1;
direction=true;//true = up false = down
nextFloor=10;
}
void input(){//input function
    int x,y;
    cout << "\nInput passengers to pick up by inputing the floor of pickup then the floor to drop off and type '0' to move the elevator\n";
    while(1){
    cout << "\nGet on: ";
    cin >> x;
    if(x==0){
        return;
    }
    cin >> y;
    getOn(x,y);
    }

    }

void directional(){//direction check for elevator
    node* info = head;
    while(info!=NULL){
        if((info->getOn>=floorNumber&&info->getOn!=0&&direction==1)||(info->getOn==0&&info->getOff>=floorNumber&&direction==1)){
           return;}
        if((info->getOn<=floorNumber&&info->getOn!=0&&direction==0)||(info->getOn==0&&info->getOff<=floorNumber&&direction==0)){
           return;}
        if(info->next==NULL){//if nothing is in the current direction
            cout << "\nNo more request in the current direction either input more get ons or type move to switch directions";
            input();
            info=head;
            while(info!=NULL){//checks new inputs to see what direction to go in
            if((info->getOn>=floorNumber&&info->getOn!=0&&direction==1)||(info->getOn==0&&info->getOff>=floorNumber&&direction==1)){
            return;}
            if((info->getOn<=floorNumber&&info->getOn!=0&&direction==0)||(info->getOn==0&&info->getOff<=floorNumber&&direction==0)){
            return;;
            }
            info=info->next;
                if(info==NULL){//swaps direction
                    if(direction==true){
                        direction=false;
                        return;
                    }
                    if(direction==false){
                        direction=true;
                        return;
                    }
                }
        }
        }
        info=info->next;
    }
    return;
}
void getOn(int x,int y){
    node* info = new node;
    info->getOn=x;
    info->getOff=y;
    if(tail!=NULL){//adds node to back of list
    node* temp = tail;
    info->next=NULL;
    info->prev=temp;
    temp->next=info;
    tail=info;
    }
    if(tail==NULL){//creates new list
        info->prev=NULL;
        info->next=NULL;
        head = info;
        tail = info;
    }

}
void MOVE(){
    node* info = head;
    directional();//direction check function
    if(direction==true){
            nextFloor=10;
        while(info!=NULL){//loop to figure out which floor is the closest in the current direction
            if(info->getOn<=nextFloor&&info->getOn!=0&&info->getOn>=floorNumber){
                nextFloor=info->getOn;
            }
            if(info->getOn==0&&info->getOff<=nextFloor&&info->getOff>=floorNumber){
                nextFloor=info->getOff;
            }
            info=info->next;
            }
        }
    if(direction==false){
        nextFloor=1;
        while(info!=NULL){//loop to figure out which floor is the closest in the current direction
            if(info->getOn==0&&info->getOff>=nextFloor&&info->getOff<=floorNumber){
                nextFloor=info->getOff;

            }
            if(info->getOn>=nextFloor&&info->getOn!=0&&info->getOn<=floorNumber){
                nextFloor=info->getOn;
            }
            info=info->next;
        }
    }
    info = head;
    floorNumber=nextFloor;
        while(info!=NULL){
                if(info->getOn==floorNumber){//passenger enters
                cout << "\nPassenger on at" << floorNumber;
                info->getOn=0;
            }
            if(info->getOff==floorNumber&&info->getOn==0){//passenger leaves
                    cout << "\nPassenger off at" << floorNumber;

                    //ifs for reorganizing the list once the passenger leaves
                    if(info!=head&&info!=tail){//middle node
                        info->next->prev=info->prev;
                        info->prev->next=info->next;
                        info=info->prev;
                   }

                    else if(info==head&&info==tail){//last node
                        delete info;
                        head = NULL;
                        tail = NULL;
                        return;
                    }
                    else if(info==tail){//tail
                        info= info->prev;
                        info->next=NULL;
                        tail = info;
                    }
                    else if(info==head){//head
                        info=info->next;
                        info->prev = NULL;
                        head = info;
                    }

                    }

                if(info!=NULL){
                info=info->next;
                }
            }
            if(head!=NULL){//repeats move function if the list is not empty
                MOVE();
            }
            if(head==NULL){//elevator returns to floor 1 waiting for more commands
                nextFloor=10;
                floorNumber=1;
                return;
            }
        }
};
int main()
{
    int x = 1;
    elevator a;
    cout << "Peter Pasek Elevator Simulation";
    while(x!=0){
    a.input();
    a.MOVE();
    cout << "\nElevator has completed all requests and is on floor 1\nEnter 1 to enter more requests or enter 0 to exit program";
    cin >> x;
    }
    return 0;
}
