#include <iostream>
using namespace std;

class Vehicle{
	private:
		int vehicleID;
		string vehicleType;
		int entryTime;
		int parkingDuration;
		double parkingFee;
		bool isOccupied;
		
	public:
		Vehicle(){
			this->vehicleID = 0;
			this->vehicleType = "";
			this->entryTime = 0;
			this->parkingDuration = 0;
			this->isOccupied = false;
		}
		
		Vehicle(int id, string type, int time, int dur, double fee, bool occ){
			this->vehicleID = id;
			this->vehicleType = type;
			this->entryTime = time;
			this->parkingDuration = dur;
			this->parkingFee = fee;
			this->isOccupied = occ;
		}
		
		//get
		
		int getID() const{
			return this->vehicleID;
		}
		
		string getType() const{
			return this->vehicleType;
		}
		
		int getTime() const{
			return this->entryTime;
		}
		
		int getDur() const{
			return this->parkingDuration;
		}
		
		double getFee() const{
			return this->parkingFee;
		}
		
		bool getOcc() const{
			return this->isOccupied;
		}
		
		//set
		
		void setID(int id){
			this->vehicleID = id;
		}
		
		void setType(string type){
			this->vehicleType = type;
		}
		
		void setTime(int time){
			this->entryTime = time;
		}
		
		void setDur(int dur){
			this->parkingDuration = dur;
		}
		
		void setFee(double fee){
			this->parkingFee = fee;
		}
		
		void setOcc(bool occ){
			this->isOccupied = occ;
		}
		
		double calculateFee() const{
			
			double factor = 0.00;
			double 2hrs = 0.00;
			if (vehicleType == "car" || vehicleType == "CAR"){
				factor = 6.00;
			}
			
			if (vehicleType == "motorcycle" || vehicleType == "MOTORCYCLE"){
				factor = 4.00;
			}
			
			if (vehicleType == "bicycle" || vehicleType == "BICYCLE"){
				factor = 2.00;
			}
			
			if ((entryTime > 6&&entryTime < 9)||(entryTime > 15&&entryTime < 18)){
				2hrs = (2*factor) + (2*factor)*0.3;
			}
			else{
				2hrs = (2*factor) - (2*factor)*0.05;
			}
			
			return 2*2hrs + (parkingDuration - 2)*factor - (parkingDuration - 2)*factor*0.1;
		}
		void display(){
			cout<<vehicleID<<" Loai phuong tien: "<<vehicleType<<" Gio vao bai: "<<entryTime<<" So gio do: "<<parkingDuration<<" Phi do xe: "<<parkingFee<<endl;
		}
};

class ParkingLot{
	private:
		int parkID;
		char size;
		Vehicle vehicle1; Vehicle vehicle2; Vehicle vehicle3;
		bool hasVehicle1, hasVehicle2, hasVehicle3;
		
	public:
		
		ParkingLot(){
			this->parkID = 0;
			this->size = 0;
			this->hasVehicle1 = false;
			this->hasVehicle2 = false;
			this->hasVehicle3 = false;
		}
		ParkingLot(int id, char size){
			this->parkID = id;
			this->size = size;
			this->hasVehicle1 = false;
			this->hasVehicle2 = false;
			this->hasVehicle3 = false;
		}
		
		bool addVehicle(const Vehicle& v){
			
			if(!hasVehicle1){
				vehicle1 = v;
				hasVehicle1 = true;
				return true;
			}
			
			if(!hasVehicle2){
				vehicle2 = v;
				hasVehicle2 = true;
				return true;
			}
			
			if(!hasVehicle3){
				vehicle3 = v;
				hasVehicle3 = true;
				return true;
			}
			
			return false;
		}
		
		bool removeVehicle (int vID){
			if(vehicle1.getID() == vID){
				vehicle1 = Vehicle();
				hasVehicle1 = false;
				return true;
			}
			
			if(vehicle2.getID() == vID){
				vehicle2 = Vehicle();
				hasVehicle2 = false;
				return true;
			}
			
			if(vehicle3.getID() == vID){
				vehicle3 = Vehicle();
				hasVehicle3 = false;
				return true;
			}
		}
		
		void DisplayLotInfo(){
			cout<<"BAI XE "<<parkID<<", size "<<size<<": \n";
			vehicle1.display();
			vehicle2.display();
			vehicle3.display();
		}
};


class SystemInterface{
	private:
		ParkingLot parkingLot1; ParkingLot parkingLot2; ParkingLot parkingLot3;
		bool hasLot1, hasLot2, hasLot3;
		
	public:
		int main(){
			return 0;
		} 
};
