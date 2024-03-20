/*
 * AutomataStructs.h
 *
 *  Created on: 09/12/2023
 *      Author: micron
 */
#include <stdint.h>
#include <std_msgs/msg/int8.h>
#pragma once
enum critical_as_state {
	OFF=1,
	READY=2,
	DRIVING=3,
	EMERGENCY=4,
	FINISH=5,
	UNKNOWN_STATE

};
enum critical_as_mission {
    ACCELERATION=1,
    SKIDPAD=2,
    TRACKDRIVE=3,
    BRAKEDRIVE=4,
    INSPECTION=5,
    AUTOCROSS=6,
    UNKNOWN_MISSION
};
template<typename T>
class wrapper_int8{
	public: 
		T value;

		wrapper_int8(){
			value = (T)0;
		}
		wrapper_int8(T incoming_value){

			this->value = incoming_value;
			msg = *(std_msgs__msg__Int8__create());
			msg.data = incoming_value;
		}
		std_msgs__msg__Int8 get(){
		    return msg;
		}
		void set(std_msgs__msg__Int8 incoming_msg){
		    this->msg = incoming_msg;
		    this->value= (T)incoming_msg.data;


		}
		void set(T incoming_value){
		    this->value=incoming_value;
		    this->msg= *(std_msgs__msg__Int8__create());
		    msg.data = (int8_t)incoming_value;
		}
		void operator=(T incoming_value){
		    this->set(incoming_value);
		}
		void operator=(std_msgs__msg__Int8 incoming_msg){
		    this->set(incoming_msg);
		}
		bool operator!=(wrapper_int8<T> other){
		    return this->value != other.value;
		}


	private: 
		std_msgs__msg__Int8 msg;

};



