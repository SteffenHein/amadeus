#!/usr/bin/perl
#------------------------------------------------------------------------------#
#                                                                              #
#  Directory checksum computation perl script                                  #
#                                                                              #
#  (C) SHEIN; Munich, April 2020                             Steffen Hein      #
#  [ Update: December 19, 2021 ]                          <contact@sfenx.de>   #
#                                                                              #
#------------------------------------------------------------------------------#
BEGIN { push @INC, './'}
use warnings 'all';
use Env;
use strict;
use cksmd5;
$ENV{OSTYPE}="linux";

#------------------------------------------------------------------------------#
my ( @files, @args, $directory, $string, $i );

#-----------------------------------------------------------------------------#
# check command line:
#
#if ( ! $ARGV[0] ) {
#    die (
#"Usage: cksmd5.pl DIRECTORY \n"
#    );
#}

#-----------------------------------------------------------------------------#

$directory = "./";
if ( $ARGV[0] ) {
    $directory = $ARGV[0];
}

#------------------------------------------------------------------------------#
# Writing new final package checksum:
#
# check / open  directory :
#
opendir( DIR, $directory )
  || die ( "can't open directory " . $directory . "\n" );
@files = grep -T, readdir(DIR);
close(DIR);

$string = &cksmd5( $directory, "CHECKSUM.MD5" );
print STDOUT ($string);

#-------------------------------------------------------------------------------#
print STDOUT "Done !\n";
