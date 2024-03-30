#include <usb_names.h>

#define MANUFACTURER_NAME    {'P','i','g','a','t','r','o','n',' ','I','n','d','u','s','t','r','i','e','s'}
#define MANUFACTURER_NAME_LEN 19
#define PRODUCT_NAME    {'Q','U','A','N','T','I','Z','E','R'}
#define PRODUCT_NAME_LEN 9

struct usb_string_descriptor_struct usb_string_manufacturer_name = {
        2 + MANUFACTURER_NAME_LEN * 2,
        3,
        MANUFACTURER_NAME
};

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + PRODUCT_NAME_LEN * 2,
        3,
        PRODUCT_NAME
};