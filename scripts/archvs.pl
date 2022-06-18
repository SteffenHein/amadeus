#!/usr/bin/perl
#------------------------------------------------------------------------------#
#                                                                              #
#  AMADEUS archive creation perl script                                        #
#                                                                              #
#  (C) SHEIN; Munich, April 2020                             Steffen Hein      #
#  [ Update: June 08, 2022 ]                              <contact@sfenx.de>   #
#                                                                              #
#------------------------------------------------------------------------------#
BEGIN { push @INC, './'}
use warnings 'all';
use Env;
use strict;
use cksmd5;
$ENV{OSTYPE}="linux";

#------------------------------------------------------------------------------#
my ( @dirtree,  @path,    @files,    @args );
my ( @srclist, @ziplist,  @tgzlist, @modlist, @text );
my ( $portname, $release, $distname, $directory, $infile, $outfile, $cksmd5 );
my ( $srcarch, $tararch, $tgzarch, $modarch, $gzarch, $bz2arch, $i, $j, $md5 );

#------------------------------------------------------------------------------#
$portname = "amadeus";
$release  = "v1.0r2";
$distname = $portname . "-" . $release;
$srcarch  = $distname . ".src.tar";
$tararch  = $distname . ".tar";
$tgzarch  = $distname . ".tgz";
$gzarch   = $srcarch . ".gz";
$bz2arch  = $srcarch . ".bz2";
$outfile  = "CHECKSUM.MD5";

# $md5=0/1/2: [ don't use / use only / use also ]
# FreeBSD's implementation of checksum function md5 for OSTYPE=freebsd
# GNU/Linux implementation of checksum function md5sum else
$md5=0;

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
$ziplist[ $i++ ] = $distname . "/LICENSE";
$ziplist[ $i++ ] = $distname . "/README";
$ziplist[ $i++ ] = $distname . "/INSTALL";
$ziplist[ $i++ ] = $distname . "/CONFIG.H";
$ziplist[ $i++ ] = $distname . "/bin";
$ziplist[ $i++ ] = $distname . "/default";
$ziplist[ $i++ ] = $distname . "/disp";
$ziplist[ $i++ ] = $distname . "/doc";
$ziplist[ $i++ ] = $distname . "/math";
$ziplist[ $i++ ] = $distname . "/objects";
$ziplist[ $i++ ] = $distname . "/samples";
$ziplist[ $i++ ] = $distname . "/scripts";
$ziplist[ $i++ ] = $distname . "/src";
$ziplist[ $i++ ] = $distname . "/work";
$ziplist[ $i++ ] = $distname . "/Makefile";
$ziplist[ $i++ ] = $distname . "/makefile.unx";
$ziplist[ $i++ ] = $distname . "/mk.unx";
$ziplist[ $i++ ] = $distname . "/SETUP";
#------------------------------------------------------------------------------#
# Create a new tar archive for FreeBSD port building system:
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
if ( $md5 ) {

    $outfile = "CHECKSUM.MD5";

    if ( ($md5) && ( $ENV{OSTYPE} =~ m/freebsd/ ) ) {
       @args = ("./cksmd5.pl $outfile");
    } else {
       @args = ("./md5sum.sh $outfile");
    }
    system(@args);
}    # end if

# switch back to package directory, then write directory [ tree ] checksums:
#
chdir "../../";
if ( $md5 != 1 )
{
    $i = 0;
    while ( $dirtree[$i] ) {

        # check / open  directory :
        $directory = $dirtree[$i];

        if ( opendir( DIR, $directory ) ) {
            @files = grep -T, readdir(DIR);
            close(DIR);

            @path = split ( /\//, $directory );

            $j = 0;
            until ( !$path[$j] ) {
                $outfile = $path[$j] . ".md5";
                $j++;
            }

            #         unlink $directory ."/". $outfile;
            #         unlink $directory ."/*.MD5";
            #         unlink $directory ."/*.md5";

            $cksmd5 = &cksmd5( $directory, $outfile );

            open( FILE, ">" . $directory . "/" . $outfile );
            print FILE ($cksmd5);
            close(FILE);
        }
        else {
            print "\ncan't open directory " . $directory;
        }
        $i++;
    }    # end while
}    # end if $ENV ...

#------------------------------------------------------------------------------#
# Creating achive for selected files: 
#
# switch to script directory then create archive:
#
print "\ncreating archives:";
chdir $distname . "/scripts";
print "\ntar -cvf spcf-" . $release . ".tgz\n";
@args = ("./new-spcf.sh");
system(@args);

#------------------------------------------------------------------------------#
# Create a new tgz archive [ program package ], $tgzarch:
#
# switch back to package directory, then create archives:
#
chdir "../../";

#print "\ncreating tgz-archive:";
print "\ntar -czf " . $tgzarch . "\n";
@args = ("tar -czf $tgzarch @tgzlist");
system(@args);

#print "\narchive ".$tgzarch." ready !";
#------------------------------------------------------------------------------#
# Create a new Z-compressed archive of essential sources [ $tararch.".Z" ]:
#
# switch into package directory, then create archive:
#print "\ncreating archive ".$tararch.".Z:";
print "\ntar -cf " . $tararch . "\n";
@args = ("tar -cf $tararch @ziplist");
system(@args);
print "\ncompressing to ~.7z";
@args = ("p7zip $tararch");
system(@args);

#print "\narchive ".$tararch.".7z ready !";
#------------------------------------------------------------------------------#
# Create a new tar archive for FreeBSD port building system:
#
#print "\ncreating tar archives ".$srcarch;
#print "\ncreating src.tar archives:";
print "\ntar -cf " . $srcarch . "\n";
@args = ("tar -cf $srcarch @srclist");
system(@args);
print "\ngzipping into ~.gz file";
@args = ("gzip -cf $srcarch > $gzarch");
system(@args);

#print "\narchive ".$gzarch." ready !";
print "\nbzipping into ~.bz2 file";
@args = ("bzip2 -f $srcarch");
system(@args);

#print "\narchive ".$srcarch.".bz2 ready !";
#------------------------------------------------------------------------------#
# Writing new final package checksum:
#
$directory = "./";
print "\n\nwriting final package checksum";

if ( $md5 )
{
    $outfile = "CHECKSUM.MD5";
    @args = ("rm -f $outfile");
    system(@args);

    if ( $ENV{OSTYPE} =~ m/freebsd/ ) {
       @args = ("md5 * > $outfile");
    } else {
       @args = ("md5sum * > $outfile");
    }
    system(@args);
}

# check / open  directory :
#
# outcommented 05.09.2002:
# if ( ( ( $md5 != 1 ) && ( $ENV{OSTYPE} =~ m/freebsd/ ) )
#   || ( $ENV{OSTYPE} =~ m/linux/ ) )

if ( $md5 != 1 ) # since 05.09.2002
{
    $outfile = $directory . ".md5";

    #  unlink $directory ."/". $outfile;
    #  unlink $directory ."/*.MD5";
    #  unlink $directory ."/*.md5";

    if ( opendir( DIR, $directory ) ) {
        @files = grep -T, readdir(DIR);
        close(DIR);

        $cksmd5 = &cksmd5( $directory, $outfile );

        open( FILE, ">" . $directory . "/" . $outfile );
        print FILE ($cksmd5);
        close(FILE);
    }
    else {
        print "\ncan't open directory " . $directory;
    }    # end if ( opendir )
}    # end if $ENV...

#------------------------------------------------------------------------------#
print "\nterminated !\n";
