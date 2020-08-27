/*************************************************************************/
/*  register_types.cpp                                                   */
/*************************************************************************/

#include "register_types.h"
#include "core/io/resource_importer.h"
#include "resource_importer_lottie.h"

void register_gd_lottie_types() {
	Ref<ResourceImporterLottie> lottie_spatial_loader;
	lottie_spatial_loader.instance();
	ResourceFormatImporter::get_singleton()->add_importer(lottie_spatial_loader);
}

void unregister_gd_lottie_types() {
}
