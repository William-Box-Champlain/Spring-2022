#include "AllegroInitializer.h"
AllegroInitializer::AllegroInitializer() {}
void AllegroInitializer::Initialize() 
{
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
		system("pause");
	}
	if (!al_init_image_addon())
	{
		std::cout << "error - Image Add-on not initted\n";
		system("pause");
	}
	if (!al_init_font_addon())
	{
		std::cout << "error - Font Add-on not initted\n";
		system("pause");
	}
	if (!al_init_ttf_addon())
	{
		std::cout << "error - TTF Add-on not initted\n";
		system("pause");
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "error - primitives Add-on not initted\n";
		system("pause");
	}
	if (!al_install_audio())
	{
		std::cout << "error - Audio Add-on not initted\n";
		system("pause");
	}
	if (!al_init_acodec_addon())
	{
		std::cout << "error - Audio Codec Add-on not initted\n";
		system("pause");
	}
	if (!al_reserve_samples(1))
	{
		std::cout << "error - samples not reserved\n";
		system("pause");
	}
}