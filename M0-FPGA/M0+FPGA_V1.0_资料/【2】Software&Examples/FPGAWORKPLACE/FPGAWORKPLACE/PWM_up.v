module PWM_up(
	input clk_200M,rst_n,//输入时钟,复位
	input [15:0]CCR,//capture/compare register
	output reg pwmout1,
	output reg pwmout1N
);
	reg [15:0]counter;

	
	wire delay_finish;
	
	parameter  ARR=16'd3535;//auto-reload register  define:65535
	parameter  DEADTIME=16'd20;//死区时间，以200MHz时钟计算，5ns分辨率
	
	
//计数
always @(posedge clk_200M  or negedge rst_n)
begin
    if(!rst_n)                  //复位
        begin
            counter <= 0;
            pwmout1 <= 1'b0;
				pwmout1N<= 1'b0;

        end
    else
        begin
            if(counter==ARR)     //pwm period counter
              begin
				    counter <=0;			 
					 end
            else
                counter <= counter +1'b1;
//----------------------------------------------------------------------
            if(counter<=DEADTIME)
				   begin
					pwmout1<=1'b0;
					pwmout1N<=1'b0;
					end
				else if((DEADTIME<counter)&&(counter<CCR))    //capture/compare register
					 begin
				    pwmout1 <= 1'b1;
					 pwmout1N<=1'b0;
					 end
				else if((counter>=CCR)&& (counter<=CCR+DEADTIME)) 
				   begin
					pwmout1<=1'b0;
					pwmout1N<=1'b0;
					end
            else	if(counter>=CCR+DEADTIME) 
				   begin
					pwmout1<=1'b0;
					pwmout1N<=1'b1;
					end
//----------------------------------------------------------------------					 
					 
					 
                
        end

end


endmodule
