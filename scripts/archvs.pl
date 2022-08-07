#!/usr/bin/perl
#------------------------------------------------------------------------------#
#                                                                              #
#  AMADEUS archive creation perl script                                        #
#                                                                              #
#  (C) SHEIN; Munich, April 2020                             Steffen Hein      #
#  [ Update: August 04, 2022 ]                            <contact@sfenx.de>   #
#                                                                              #
#------------------------------------------------------------------------------#
BEGIN { push @INC, './'}
use warnings 'all';
use Env;
use strict;
$ENV{OSTYPE}="linux";

#------------------------------------------------------------------------------#
my ( @dirtree,  @path,    @files,    @args );
my ( @srclist, @z7list,  @tgzlist, @modlist, @text );
my ( $portname, $release, $distname, $directory, $infile, $outfile );
my ( $srcarch, $tararch, $tgzarch, $modarch, $gzarch, $bz2arch );
my ( $i, $j, $cks );

#------------------------------------------------------------------------------#
$portname = "amadeus";
$release  = "v1.0r2";
$distname = $portname . "-" . $release;
$srcarch  = $distname . ".src.tar";
$tararch  = $distname . ".tar";
$tgzarch  = $distname . ".tgz";
$gzarch   = $srcarch . ".gz";
$bz2arch  = $srcarch . ".bz2";
$outfile  = ".sha256";

# $cks=[0]1: [ don't] compute sha256 checksums
$cks=1;

#------------------------------------------------------------------------------#
# the directory tree of $distname 
#
$i = 0;
$dirtree[ $i++ ] = $distname;
$dirtree[ $i++ ] = $distname . "/bin";
$dirtree[ $i++ ] = $distname . "/default";
$dirtree[ $i++ ] = $distname . "/disp";
$dirtree[ $i++ ] = $distname . "/doc";
$dirtree[ $i++ ] = $distname . "/math";
$dirtree[ $i++ ] = $distname . "/objects";
$dirtree[ $i++ ] = $distname . "/samples";
$dirtree[ $i++ ] = $distname . "/scripts";
$dirtree[ $i++ ] = $distname . "/src";
$dirtree[ $i++ ] = $distname . "/work";
#------------------------------------------------------------------------------#
# the list of files stored in $tgzarch
#
$i = 0;
$tgzlist[ $i++ ] = $distname . "/LICENSE";
$tgzlist[ $i++ ] = $distname . "/README";
$tgzlist[ $i++ ] = $distname . "/INSTALL";
$tgzlist[ $i++ ] = $distname . "/CONFIG.H";
$tgzlist[ $i++ ] = $distname . "/bin";
$tgzlist[ $i++ ] = $distname . "/default";
$tgzlist[ $i++ ] = $distname . "/disp";
$tgzlist[ $i++ ] = $distname . "/doc";
$tgzlist[ $i++ ] = $distname . "/math";
$tgzlist[ $i++ ] = $distname . "/objects";
$tgzlist[ $i++ ] = $distname . "/samples";
$tgzlist[ $i++ ] = $distname . "/scripts";
$tgzlist[ $i++ ] = $distname . "/src";
$tgzlist[ $i++ ] = $distname . "/work";
$tgzlist[ $i++ ] = $distname . "/Makefile";
$tgzlist[ $i++ ] = $distname . "/makefile.unx";
$tgzlist[ $i++ ] = $distname . "/mk.unx";
$tgzlist[ $i++ ] = $distname . "/SETUP";
#------------------------------------------------------------------------------#
# The Z-compressed archive of the following [ essential ] sources; $tararch:
#
$i = 0;
$z7list[ $i++ ] = $distname . "/LICENSE";
$z7list[ $i++ ] = $distname . "/README";
$z7list[ $i++ ] = $distname . "/INSTALL";
$z7list[ $i++ ] = $distname . "/CONFIG.H";
$z7list[ $i++ ] = $distname . "/bin";
$z7list[ $i++ ] = $distname . "/default";
$z7list[ $i++ ] = $distname . "/disp";
$z7list[ $i++ ] = $distname . "/doc";
$z7list[ $i++ ] = $distname . "/math";
$z7list[ $i++ ] = $distname . "/objects";
$z7list[ $i++ ] = $distname . "/samples";
$z7list[ $i++ ] = $distname . "/scripts";
$z7list[ $i++ ] = $distname . "/src";
$z7list[ $i++ ] = $distname . "/work";
$z7list[ $i++ ] = $distname . "/Makefile";
$z7list[ $i++ ] = $distname . "/makefile.unx";
$z7list[ $i++ ] = $distname . "/mk.unx";
$z7list[ $i++ ] = $distname . "/SETUP";
#------------------------------------------------------------------------------#
#
$i = 0;
$srclist[ $i++ ] = $distname;
$srclist[ $i++ ] = "LICENSE";
$srclist[ $i++ ] = "README";
$srclist[ $i++ ] = "INSTALL";

#------------------------------------------------------------------------------#
# Writing special directory checksums:
#
print "\n\nwriting directory checksums";

if ( $cks ) {
    $outfile = ".sha256";
    @args = ("./sha256sum.sh $outfile");
    system(@args);

    $outfile = ".md5";
    @args = ("./md5sum.sh $outfile");
    system(@args);
} # end if

# switch back to package directory, then write directory [ tree ] checksums:
#
chdir "../../";
#------------------------------------------------------------------------------#
# Create tgz archive:
#
print "\ncreating tgz-archive:";
@args = ("tar -czf $tgzarch @tgzlist");
system(@args);
#------------------------------------------------------------------------------#
# Create a new p7zip-compressed archive of essential sources:
print "\ncreating archive $tararch";
@args = ("tar -cf $tararch @z7list");
system(@args);

print "\ncompressing to ~.7z";
@args = ("p7zip -k $tararch");
system(@args);
#------------------------------------------------------------------------------#
print "\ncreating tar archive:";
@args = ("tar -cf $srcarch @srclist");
system(@args);

print "\ngzipping into ~.gz file";
@args = ("gzip -cf $srcarch > $gzarch");
system(@args);

print "\nbzipping into ~.bz2 file";
@args = ("bzip2 -f $srcarch > $bz2arch");
system(@args);
#------------------------------------------------------------------------------#
# Writing new final package checksum:
#
$directory = "../../";
print "\n\nwriting final package checksum";

if ( $cks )
{
    $outfile = "SHA256SUMS";
    @args = ("rm -f $outfile");
    system(@args);
    @args = ("openssl sha256 * > $outfile");
    system(@args);

    $outfile = "MD5SUMS";
    @args = ("rm -f $outfile");
    system(@args);
    @args = ("md5sum * > $outfile");
    system(@args);
}
#------------------------------------------------------------------------------#
print "\nterminated !\n";
