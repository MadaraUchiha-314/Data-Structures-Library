	#include <fstream>
	#include <iostream>

	using namespace std;

	struct BMP_Header
	{
		public :
	
		char id[2];
		unsigned int total_image_size;
		short int app_data1,app_data2;
		unsigned int offset;
	

	} __attribute__ ((packed));

	struct DIB_Header 
	{
		public :

		unsigned int dib_header_size;
		int image_width;
		int image_height;
		short int no_colour_planes;
		short int colour_depth;
		unsigned int compression_method;
		unsigned int raw_image_size;
		unsigned int horizontal_resolution;
		unsigned int vertical_resolution;
		unsigned int num_colours_palette;
		unsigned int imp_colours_used;
	

	} __attribute__ ((packed));



	int main ()
	{
		int index=0;
		int index1=0;
		BMP_Header bmp_header;
		DIB_Header dib_header;
		char pixel_array[16];
		char array1[54];
		char *ptr;
		

		bmp_header.id[0]='B';
		bmp_header.id[1]='M';
		bmp_header.total_image_size=70;
		bmp_header.app_data1=0;
		bmp_header.app_data2=0;
		bmp_header.offset=54;

	
		dib_header.dib_header_size=40;
		dib_header.image_width=2;
		dib_header.image_height=2;
		dib_header.no_colour_planes=1;
		dib_header.colour_depth=24;
		dib_header.compression_method=0;
		dib_header.raw_image_size=16;
		dib_header.horizontal_resolution=2835;
		dib_header.vertical_resolution=2835;
		dib_header.num_colours_palette=0;	
		dib_header.imp_colours_used=0;

		pixel_array[index++]=0;
		pixel_array[index++]=0;
		pixel_array[index++]=255;

		pixel_array[index++]=255;
		pixel_array[index++]=255;
		pixel_array[index++]=255;
	
		pixel_array[index++]=0;
		pixel_array[index++]=0;

		pixel_array[index++]=255;
		pixel_array[index++]=0;
		pixel_array[index++]=0;

		pixel_array[index++]=0;
		pixel_array[index++]=255;
		pixel_array[index++]=0;

		pixel_array[index++]=0;
		pixel_array[index++]=0;

		ptr=(char*)&bmp_header;

		/*for (int i=0;i<sizeof (bmp_header);i++)
		{
			
			array1[index1++]=*ptr++;
		}
		ptr=(char*)&dib_header;
		for (int i=0;i<sizeof (dib_header);i++)
		{
			
			array1[index1++]=*ptr++;
		}*/	
	
	// Image Made
		fstream file;
		file.open ("abc.bmp",ios::out |ios::binary);
		//file.write ((char*)array1,54);
		file.write ((char*)&bmp_header,sizeof(bmp_header));
		file.write ((char*)&dib_header,sizeof (dib_header));
		file.write ((char*)pixel_array,sizeof (pixel_array));
	
	
	
		file.close ();

	return 0;
	}


	
		

	


