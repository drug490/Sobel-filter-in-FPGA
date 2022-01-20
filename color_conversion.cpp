#include "color_conversion.h"
 
void color_conversion(hls::stream<axis_t> &stream_in, hls::stream<axis_t> &stream_out) {
 
// clang-format off
    #pragma HLS INTERFACE axis register both  port=stream_in
    #pragma HLS INTERFACE axis register both  port=stream_out
    #pragma HLS INTERFACE ap_ctrl_none  port=return
 // clang-format on
 

	    xf::cv::Mat<XF_8UC3, HEIGHT, WIDTH, XF_NPPC1> img_buf_0(HEIGHT, WIDTH);
	    xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> img_buf_1(HEIGHT, WIDTH);
	    xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> img_buf_1a(HEIGHT, WIDTH);
	    xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> img_buf_1b(HEIGHT, WIDTH);
	    xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> img_buf_2(HEIGHT, WIDTH);
	    xf::cv::Mat<XF_8UC3, HEIGHT, WIDTH, XF_NPPC1> img_buf_3(HEIGHT, WIDTH);

//    	 clang-format off
			#pragma HLS DATAFLOW
//		 clang-format on
    xf::cv::AXIvideo2xfMat(stream_in, img_buf_0);


    xf::cv::rgb2gray<XF_8UC3, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(img_buf_0, img_buf_1);
    xf::cv::Sobel<0, 3, XF_8UC1, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1, false>(img_buf_1, img_buf_1a, img_buf_1b);
    xf::cv::addWeighted<XF_8UC1, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(img_buf_1a, 0.5, img_buf_1b, 0.5, 0, img_buf_2);
    xf::cv::gray2rgb<XF_8UC1, XF_8UC3, HEIGHT, WIDTH, XF_NPPC1>(img_buf_2, img_buf_3);


    xf::cv::xfMat2AXIvideo(img_buf_3, stream_out);
}
