module FSMC_Data(addr,FMC_data,
                 wr,rd,
					  rddat0,rddat1,rddat2,rddat3,rddat4,rddat5,rddat6,rddat7,rddat8,rddat9,rddat10,rddat11,rddat12,
					  wrdat0,wrdat1,wrdat2,wrdat3,wrdat4,wrdat5,wrdat6,wrdat7,wrdat8,wrdat9,wrdat10,wrdat11	//连接FPGA内部模块，将从STM32读入的数据传出
  
                );


  input [7:0] addr;       //地址线  
  inout [15:0] FMC_data;   //数据线
  input wr,rd;             //读写控制,低电平有效
  input [15:0]rddat0,rddat1,rddat2,rddat3,rddat4,rddat5,rddat6,rddat7,rddat8,rddat9,rddat10,rddat11,rddat12;		//连接FPGA内部模块，将需要传输到STM32的数据读入
  output reg [15:0]wrdat0,wrdat1,wrdat2,wrdat3,wrdat4,wrdat5,wrdat6,wrdat7,wrdat8,wrdat9,wrdat10,wrdat11;	//连接FPGA内部模块，将从STM32读入的数据传出
  
 

  reg [15:0]  temp_read_data;  //数据暂存
  
  assign FMC_data = (rd==1'b0)? temp_read_data: 16'hzzzz;  //不进行rd时，将data设为高阻态

  always @(posedge wr )//STM32向FPGA写数据，NWE下降沿写入到FMC_data，稳定后输出到FPGA内其他模块
  begin
     case(addr[7:0])
	  
	  	 8'b0000_0001://0x6000 0001
			begin
			wrdat0<=FMC_data;
			end 
	     8'b0000_0010://0x6000 0002
			begin
			wrdat1<=FMC_data;
			end 
		 8'b0000_0011://0x6000 0003
			begin
			wrdat2<=FMC_data;
			end 
		 8'b0000_0100://0x6000 0004
			begin
			wrdat3<=FMC_data;
			end 
		 8'b0000_0101://0x6000 0005
			begin
			wrdat4<=FMC_data;
			end 
		 8'b0000_0110://0x6000 0006
			begin
			wrdat5<=FMC_data;
			end 
		 8'b0000_0111://0x6000 0007
			begin
			wrdat6<=FMC_data;
			end 
		 8'b0000_1000://0x6000 0008
			begin
			wrdat7<=FMC_data;
			end 
		 8'b0000_1001://0x6000 0009
			begin
			wrdat8<=FMC_data;
			end 
		 8'b0000_1010://0x6000 000a
			begin
			wrdat9<=FMC_data;
			end 
		 8'b0000_1011://0x6000 000b
			begin
			wrdat10<=FMC_data;
			end 
		8'b0000_1100://0x6000 000c
			begin
			wrdat11<=FMC_data;
			end 
       default:begin
       wrdat8<=16'h0001;wrdat7<=16'h0000;wrdat6<=16'h0000;wrdat5<=16'h0000;wrdat4<=16'h0000;
		 wrdat3<=16'h0000;wrdat2<=16'h0000;wrdat1<=16'h0000;wrdat0<=16'h0000;
       end
			
			endcase
	end
	  

 

 always @(*  )//STM32向FPGA读数据
    begin
     case(addr[7:0])

		 8'b1000_0001://0x6000 0081
			begin
			temp_read_data<=16'd1234;
			end 
		 8'b1000_0010://0x6000 0082
			begin
			temp_read_data<=16'd1236;
			end 
		 8'b1000_0011://0x6000 0083
			begin
			temp_read_data<=rddat2;
			end
		 8'b1000_0100://0x6000 0084
			begin
			temp_read_data<=rddat3;
			end 
		 8'b1000_0101://0x6000 0085
			begin
			temp_read_data<=rddat4;
			end 
		 8'b1000_0110://0x6000 0086
			begin
			temp_read_data<=rddat5;
			end 
		 8'b1000_0111://0x6000 0087
			begin
			temp_read_data<=rddat6;
			end 
		 8'b1000_1000://0x6000 0088
			begin
			temp_read_data<=rddat7;
			end 
	    8'b1000_1001://0x6000 0089
			begin
			temp_read_data<=rddat8;
			end 
		 8'b1000_1010://0x6000 008a
			begin
			temp_read_data<=rddat9;
			end 
		 8'b1000_1011://0x6000 008b
			begin
			temp_read_data<=rddat10;
			end 
		 8'b1000_1100://0x6000 008c
			begin
			temp_read_data<=rddat11;
			end 
		 8'b1000_1101://0x6000 008d
			begin
			temp_read_data<=rddat12;
			end 
       default:
		 begin
		 temp_read_data<=16'd5678;//数据地址错误返回5678
       end
			
			endcase
	end
	  
  
endmodule