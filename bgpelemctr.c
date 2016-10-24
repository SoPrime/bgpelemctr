#include <stdio.h>
#include <bgpstream.h>

int main()
{
        bgpstream_t *bs = bs = bgpstream_create();
        bgpstream_record_t *bs_record = bgpstream_record_create();

        // get only routeviews updates from saopaulo
        bgpstream_add_filter(bs, BGPSTREAM_FILTER_TYPE_PROJECT, "routeviews");
        bgpstream_add_filter(bs, BGPSTREAM_FILTER_TYPE_COLLECTOR, "route-views.saopaulo");
        bgpstream_add_filter(bs, BGPSTREAM_FILTER_TYPE_RECORD_TYPE, "updates");

        bgpstream_add_interval_filter(bs,1476728093,1476728100);

        if(bgpstream_start(bs) < 0)
        {
                fprintf(stderr, "ERROR: Could not init BGPStream\n");
                return -1;
        }

        int get_next_ret = 0;
        int elem_counter = 0;

        bgpstream_elem_t *bs_elem = NULL;

        for(get_next_ret = bgpstream_get_next_record(bs, bs_record); get_next_ret > 0; get_next_ret = bgpstream_get_next_record(bs, bs_record))
        {
                putchar('.');
                fflush(stdout);
                if(bs_record->status == BGPSTREAM_RECORD_STATUS_VALID_RECORD)
                {
                        while((bs_elem = bgpstream_record_get_next_elem (bs_record)) != NULL)
                        {
                                elem_counter++;
                        }
                }
        }

        printf("\tRead %d elems\n", elem_counter);

        bgpstream_record_destroy(bs_record);
        bgpstream_destroy(bs);

        return 0;
}

