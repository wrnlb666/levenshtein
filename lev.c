#include "lev.h"

static inline int32_t min( int32_t x, int32_t y )
{
    return ( x < y ? x : y );
}

static inline int32_t lev_impl( const char* s1, const char* s2, int32_t l1, int32_t l2, int32_t **cache )
{
    if ( cache[l1][l2] != -1 ) return cache[l1][l2];

    if ( l1 == 0 )
    {
        cache[l1][l2] = l2;
        return l2;
    }
    if ( l2 == 0 )
    {
        cache[l1][l2] = l1;
        return l1;
    }

    if ( s1[l1-1] == s2[l2-1] )
    {
        int32_t temp1 = lev_impl( s1, s2, l1-1, l2-1, cache );
        cache[l1][l2] = temp1;
        return temp1;
    }

    int32_t temp2 =  min( lev_impl( s1, s2, l1-1, l2-1, cache ), 
                min( lev_impl( s1, s2, l1-1, l2, cache ), lev_impl( s1, s2, l1, l2-1, cache ) ) ) + 1;
    cache[l1][l2] = temp2;
    return temp2;
}

int32_t lev( const char* s1, const char* s2 )
{
    int32_t l1 = strlen(s1);
    int32_t l2 = strlen(s2);

    int32_t **cache = malloc( sizeof (int32_t*) * ( l1 + 1 ) );
    for ( int32_t i = 0; i < l1 + 1; i++ )
    {
        cache[i] = malloc( sizeof (int32_t) * ( l2 + 1 ) );
        memset( cache[i], -1, sizeof (int32_t) * ( l2 + 1 ) );
    }
    
    int32_t result = lev_impl( s1, s2, l1, l2, cache );

    for ( int32_t i = 0; i < l1 + 1; i++ )
    {
        free( cache[i] );
    }
    free(cache);

    return result;
}
