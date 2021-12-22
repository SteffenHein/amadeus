#!/usr/bin/perl
#------------------------------------------------------------------------------#
#                                                                              #
#  Directory checksum perl script                                              #
#                                                                              #
#  (C) SHEIN; Munich, April 2020                             Steffen Hein      #
#  [ Update: December 19, 2021 ]                          <contact@sfenx.de>   #
#                                                                              #
#------------------------------------------------------------------------------#
Cksmd5::cksum;

#------------------------------------------------------------------------------#
BEGIN { push @INC, './'}
use warnings 'all';
use Env;
use strict;
use cksmd5;
$ENV{OSTYPE}="linux";
#use Digest::MD5 qw( md5_hex );		# declaration (1) [ option (1) ]
use Digest::MD5;    			# declaration (2) [ option (2) ]

#------------------------------------------------------------------------------#
sub cksmd5 {

#------------------------------------------------------------------------------#
    my (@files);
    my ( $directory, $content, $cksmd5, $cksum, $fct, $fname, $time, $i );

#------------------------------------------------------------------------------#
    # in option (2) only:  reset Digest::MD5
    $fct = Digest::MD5->new;

#------------------------------------------------------------------------------#
    #
    # Writing directory checksum:
    #
    $directory = $_[0];

    if ( $_[1] ) {
        $fname = $_[1];
    }
    else {
        $fname = "CHECKSUM.MD5";
    }

    if ( opendir( DIR, $directory ) ) {
        @files = sort readdir(DIR);
        close(DIR);

        $cksmd5 = "[file: " . $fname . "]\n";

        $time = time();
        $time = localtime($time);

        $cksmd5 = $cksmd5 . "created: " . $time . "\n";
        $cksmd5 = $cksmd5 . "----------------------------------------";
        $cksmd5 = $cksmd5 . "---------------------------------------\n";
        $i      = 2;
        while ( $files[$i] ) {
            if ( ( !( $files[$i] =~ m/$fname/ ) )

              && ( !( $files[$i] =~ m/\.md5/ ) )
              && ( !( $files[$i] =~ m/\.MD5/ ) )
              && ( open( FILE, "<" . $directory . "/" . $files[$i] ) ) )
            {

                $content = "";
                read( FILE, $content, 1.E8 );
                close(FILE);

                # option (1) [ requires declaration (1) ]:
                # $cksum  = md5_hex($content); # end option (1)
                # test example should yield:
                # 6df23dc03f9b54cc38a0fc1483df6e21 = md5_hex("foobarbaz");
                #
                # option( 2 ) [ requires declaration (2) ]:
                $fct = Digest::MD5->reset;
                $fct->add($content);
                $cksum = $fct->hexdigest;      # end option (2)

                $cksmd5 =
                  $cksmd5 . "MD5( " . $files[$i] . " ) = " . $cksum . "\n";
            }
            elsif ( ( !( $files[$i] =~ m/$fname/ ) )

              && ( !( $files[$i] =~ m/\.md5/ ) )
              && ( !( $files[$i] =~ m/\.MD5/ ) ) )
            {
                $fct = Digest::MD5->reset;
                $fct->add( $files[$i] );
                $cksum = $fct->hexdigest;

                # alternatively:
                #    $cksum  = &md5_hex( $files[$i] );

                $cksmd5 =
                  $cksmd5 . "MD5( " . $files[$i] . " ) = " . $cksum . "\n";

                #          print "Can't open file ".$files[$i]."\n";
            }    # end if ( open ( FILE ,...))
            $i++;
        }    # end while ( $files[$i] ...)
    }
    else {
        $cksmd5 = "Can't open directory " . $directory . "\n";
    }    # end if ( opendir ... )
    $cksmd5;
}
#------------------------------------------------------------------------------#
