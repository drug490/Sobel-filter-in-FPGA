#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.hpp"
#include "common/xf_utility.hpp"
#include "common/xf_infra.hpp"
#include <ap_axi_sdata.h>
 
#include "imgproc/xf_rgb2hsv.hpp"
#include "imgproc/xf_cvt_color.hpp"
#include "imgproc/xf_cvt_color_1.hpp"
#include "imgproc/xf_sobel.hpp"
#include "imgproc/xf_add_weighted.hpp"

 
static constexpr int WIDTH = 640;
static constexpr int HEIGHT = 480;
 
typedef ap_axiu<24,1,1,1> axis_t;
 
void color_conversion(hls::stream<axis_t> &stream_in1, hls::stream<axis_t> &stream_out) ;
