/*****************************************************************************/

/*
 *      lsftdi.c -- lspci like utility for FTDI USB devices
 *
 *      Copyright (C) 2003-2017
 *        Intra2net AG and the libftdi developers (opensource@intra2net.com)
 *      Copyright (C) 2018
 *        Vidir Alexander Jonsson (valex@valex.is)
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 */

/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <libftdi1/ftdi.h>

static void usage(void)
{
    fprintf(stderr, "usage: lsftdi [-h|--help]\n");
    exit(1);
}

int main(int argc, char **argv)
{
    int ret, ch = 0, i = 0;
    struct ftdi_context *ftdi;
    struct ftdi_device_list *devlist, *curdev;
    char manufacturer[128], description[128];
    int retval = EXIT_SUCCESS;

    struct option longopts[] = {
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    while ((ch = getopt_long(argc, argv, "h", longopts, NULL)) != -1) 
    {
        switch (ch)
        {
            case 'h':
            case '?':
            default:
            {
                usage();
            }
        }
    }

    argc -= optind;
    argv += optind;

    if (argc)
    {
        usage();
    }

    if ((ftdi = ftdi_new()) == 0)
    {
        fprintf(stderr, "ftdi_new failed\n");
        return EXIT_FAILURE;
    }

    if ((ret = ftdi_usb_find_all(ftdi, &devlist, 0, 0)) < 0)
    {
        fprintf(stderr, "ftdi_usb_find_all failed: %d (%s)\n", ret, ftdi_get_error_string(ftdi));
        retval =  EXIT_FAILURE;
        goto do_deinit;
    }

    printf("Number of FTDI devices found: %d\n", ret);

    i = 0;
    for (curdev = devlist; curdev != NULL; i++)
    {
        printf("Checking device: %d\n", i);
        if ((ret = ftdi_usb_get_strings(ftdi, curdev->dev, manufacturer, 128, description, 128, NULL, 0)) < 0)
        {
            fprintf(stderr, "ftdi_usb_get_strings failed: %d (%s)\n", ret, ftdi_get_error_string(ftdi));
            retval = EXIT_FAILURE;
            goto done;
        }
        printf("Manufacturer: %s, Description: %s\n\n", manufacturer, description);
        curdev = curdev->next;
    }
done:
    ftdi_list_free(&devlist);
do_deinit:
    ftdi_free(ftdi);

    return retval;
}
