#include <systemc.h>

SC_MODULE(FSM){
	sc_in<bool> rst, clk;
	sc_out<bool> red, yellow, green;
	
	enum State{
		RED, GREEN, YELLOW
	};

	
	
	State curr_state, next_state;
	void state_update(){
		if (rst.read())
			curr_state=RED;
		else
			curr_state=next_state;
	}
	
	void next_state_logic(){
		switch(curr_state){
            		case RED:
                		next_state = GREEN;
                		break;

	            	case GREEN:
        	        	next_state = YELLOW;
               		break;

	                case YELLOW:
            		    next_state = RED;
                	    break;

           	 	default:
                		next_state = RED;
                		break;
		}
	}

	void output_logic(){
		red.write(0);
		yellow.write(0);
		green.write(0);

		switch(curr_state){
			case RED:
				red.write(1); break;
			case YELLOW:
				yellow.write(1); break;
			case GREEN:
				green.write(1); break;
			default:
				red.write(1); break;
		}
	}

	SC_CTOR(FSM){
		std::cout<<"FSM Constructed"<<std::endl;
		curr_state=RED;
		next_state=RED;
	
		SC_METHOD(state_update); sensitive<<clk.pos();
		SC_METHOD(next_state_logic); sensitive<<clk.pos();
		SC_METHOD(output_logic); sensitive<<clk.pos();
	}

};