#include "Halide.h"
using namespace Halide;
class Blur: public Generator<Blur>{
public:
	Input<Buffer<uint8_t>> input{"input",2};
	Output<Buffer<uint8_t>> result{"result",2};
	void generate(){
		Var x,y;
		Func clamped = BoundaryConditions::repeat_edge(input);
		
		Func input_16;
		input_16(x,y)=cast<uint16_t>(clamped(x,y));
		
		Func blur_x;
		blur_x(x,y) = (input_16(x-1,y)+
				input_16(x,y)+
				input_16(x+1,y))/
				3;
		
		Func blur_y;
		blur_y(x,y) = (input_16(x,y-1)+
				input_16(x,y)+
				input_16(x,y+1))/
				3;
		
		result(x,y)=cast<uint8_t>(blur_y(x,y));
	}
};
HALIDE_REGISTER_GENERATOR(Blur,blur);
