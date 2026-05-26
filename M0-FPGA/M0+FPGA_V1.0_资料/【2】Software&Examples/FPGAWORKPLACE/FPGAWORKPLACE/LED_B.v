module LED_B(
	input CLK_50M,rst_n,//输入时钟,复位
	output reg [7:0] LED
);

	reg [32:0]counter;
	reg [7:0]LED_state;
	
always @(posedge CLK_50M  or negedge rst_n)
begin
    if(!rst_n)                  //复位
        begin
            counter <= 0;
        end
		  
	else if(counter<32'd20_000_000)
	begin
		counter<=counter+1'b1;
	end
	else
	begin

		counter<=32'b0;
		LED[7:0]<=~LED[7:0];
		
	end
end



endmodule