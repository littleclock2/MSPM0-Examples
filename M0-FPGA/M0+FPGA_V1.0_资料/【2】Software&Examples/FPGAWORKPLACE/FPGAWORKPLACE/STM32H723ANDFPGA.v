module STM32H723ANDFPGA(
	input clk_50M, rst_n,		// 50MHz时钟，pin23	和复位信号pin1	
	input NWE,NOE,//读写信号，NWE  pin83 NOE pin80
	input [7:0]ADDR,//与STM32通信的地址
	inout [15:0]DATA,//与STM32通信的数据
	output irq,
	output pwm1,pwm1n,
	inout [3:0]KEY_H,KEY_V,
	output [15:0]  wrdat0,  
	output [15:0] wrdat1,
	output [7:0]LED





);
wire clk_200M,clk_25M,PLL_locked,LED_clk;
wire [15:0] rddat0, rddat1, rddat2, rddat3, rddat4, rddat5, rddat6, rddat7, rddat8, rddat9, rddat10, rddat11, rddat12;		// 对于不同的csn,相应的rddatn有效
wire [15:0] wrdat2, wrdat3, wrdat4, wrdat5, wrdat6, wrdat7, wrdat8,wrdat9, wrdat10, wrdat11;


clk_pll	clk_pll_inst (
	.inclk0 ( clk_50M ),
	.c0 ( clk_200M ),
	.c1 ( clk_25M),
	.locked ( PLL_locked )
	);



LED_B  LED_BB(
	.CLK_50M(clk_50M),
	.rst_n(1'b1),//输入时钟,复位
	.LED(LED)
);

FSMC_Data FSMC_Data_inst
(
	.addr(ADDR) ,	// input [15:0] addr_sig
	.FMC_data(DATA) ,	// inout [15:0] FMC_data_sig
	.wr(NWE) ,	// input  wr_sig
	.rd(NOE) ,	// input  rd_sig
	.rddat0(rddat0) ,	// input [15:0] rddat0_sig
	.rddat1(rddat1) ,	// input [15:0] rddat1_sig
	.rddat2(rddat2) ,	// input [15:0] rddat2_sig 
	.rddat3(rddat3) ,	// input [15:0] rddat3_sig
	.rddat4(rddat4) ,	// input [15:0] rddat4_sig
	.rddat5(rddat5) ,	// input [15:0] rddat5_sig
	.rddat6(rddat6) ,	// input [15:0] rddat6_sig
	.rddat7(rddat7) ,	// input [15:0] rddat7_sig
	.rddat8(rddat8) ,	// input [15:0] rddat8_sig
	.rddat9(rddat9) ,	// input [15:0] rddat9_sig
	.rddat10(rddat10) ,	// input [15:0] rddat10_sig
	.rddat11(rddat11) ,	// input [15:0] rddat11_sig
	.rddat12(rddat12) ,	// input [15:0] rddat12_sig	
	
	
	.wrdat0(wrdat0) ,	// output [15:0] wrdat0_sig
	.wrdat1(wrdat1) ,	// output [15:0] wrdat1_sig
	.wrdat2(wrdat2) ,	// output [15:0] wrdat2_sig
	.wrdat3(wrdat3) ,	// output [15:0] wrdat3_sig
	.wrdat4(wrdat4) ,	// output [15:0] wrdat4_sig
	.wrdat5(wrdat5) ,	// output [15:0] wrdat5_sig
	.wrdat6(wrdat6) ,	// output [15:0] wrdat6_sig
	.wrdat7(wrdat7) ,	// output [15:0] wrdat7_sig
	.wrdat8(wrdat8) ,	// output [15:0] wrdat8_sig
	.wrdat9(wrdat9) ,	// output [15:0] wrdat9_sig
	.wrdat10(wrdat10) ,	// output [15:0] wrdat10_sig
	.wrdat11(wrdat11) 	// output [15:0] wrdat11_sig
);

PWM_up PWM_up_inst
(
	.clk_200M(clk_200M) ,	// input  clk_200M_sig
	.rst_n(1'b1) ,	// input  rst_n_sig
	.CCR(16'd2535) ,	// input [15:0] CCR_sig
	.pwmout1(pwm1) ,	// output  pwmout1_sig
	.pwmout1N(pwm1n) 	// output  pwmout1N_sig
);
	
endmodule