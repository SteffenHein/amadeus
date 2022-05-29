#!/usr/bin/perl
#------------------------------------------------------------------------------#
#                                                                              #
#  subst.pl                                                                    #
#  A handy string substitution perl script                                     #
#                                                                              #
#  (C) SHEIN; Munich, December 2021                            Steffen Hein    #
#  [ Update: December 29, 2021 ]                            <contact@sfenx.de> #
#                                                                              #
#------------------------------------------------------------------------------#
use strict;

#------------------------------------------------------------------------------#
my ( @files,      @text1 );
my ( $directory,  $infile, $output );
my ( $lines,      $mxlnes );
my ( $oldpattern, $newpattern, $i, $j, $k );

#------------------------------------------------------------------------------#
# defaults: 
#
$directory = "./";
$infile    = "";
$output    = "STDOUT";    # default output file
$mxlnes    = 10000;       # default maximum number of lines per file

#------------------------------------------------------------------------------#
# read command line:
#
$oldpattern = @ARGV[0];
$newpattern = @ARGV[1];

$i = 2;
while ( @ARGV[$i] ) {
    if ( ( @ARGV[$i] eq "o" ) || ( @ARGV[$i] eq "-o" ) || ( @ARGV[$i] eq "o" )
      || ( @ARGV[$i] eq "-O" ) )
    {
        $i++;
        $output = @ARGV[$i];
    }
    elsif ( ( @ARGV[$i] eq "d" ) || ( @ARGV[$i] eq "-d" )
      || ( @ARGV[$i] eq "D" ) || ( @ARGV[$i] eq "-D" ) )
    {
        $i++;
        $directory = @ARGV[$i];
    }
    elsif ( ( @ARGV[$i] eq "f" ) || ( @ARGV[$i] eq "-f" )
      || ( @ARGV[$i] eq "F" ) || ( @ARGV[$i] eq "-F" ) )
    {
        $i++;
        $infile = @ARGV[$i];
    }
    $i++;
}

#------------------------------------------------------------------------------#
# check command line:
#
if ( !$ARGV[1] ) {
    die (
"Usage:\nsubst.pl OLD_PATTERN NEW_PATTERN\n[ -f FILE, -d DIRECTORY, -o OUTPUT ]\n"
    );
}

#------------------------------------------------------------------------------#
# check / open  directory :
#
if ( $infile eq "" ) {
    opendir( DIR, $directory )
      || die ( "can't open directory " . $directory . "\n" );
    @files = readdir(DIR);
    close(DIR);

    if ( $output ne "STDOUT" ) {
        `mkdir $output`;
    }
    else {
        `mkdir tmp`;
    }

    $j = 0;
    while ( $files[$j] ) {
        if ( $output ne "STDOUT" ) {
            print "modifying file " . $directory . "/" . $files[$j] . "\n";
        }

        #     print "modifying file ".$directory."/".$files[$j]."\n";

        open( FILE, $directory . "/" . $files[$j] );
        @text1 = <FILE>;
        close(FILE);

        $lines = $mxlnes + 1;
        while ( ( 0 <= $lines ) && ( !( @text1[$lines] ) ) ) {
            $lines--;
        }

        if ( $lines == -1 ) {
            print "file " . $infile . " is void\n";
        }
        elsif ( ( $output ne "STDOUT" ) && ( $lines <= $mxlnes ) ) {
            print $lines, " lines in " . $files[$j] . ".\n";
        }
        elsif ( $mxlnes < $lines ) {
            print STDERR (
              "too many lines [ N > maximum = ", $mxlnes,
              " ] in " . $files[$j] . "!!!\n"
            );
        }

        #     print $lines, " lines in ".$files[$j].".\n";

        $i = 0;
        while ( $i <= $lines ) {
            $text1[$i] =~ s/$oldpattern/$newpattern/gc;
            $i++;
        }

        if ( $output ne "STDOUT" ) {
            open( FILE, ">" . $output . "/" . $files[$j] );
            print FILE (@text1);
            close(FILE);
        }
        else {

            #        print STDOUT ( @text1 );
            open( FILE, ">./tmp/" . $files[$j] );
            print FILE (@text1);
            close(FILE);
        }
        $j++;
    }

    if ( $output ne "STDOUT " ) {
        print "Done !\n";
    }
}
else {

#------------------------------------------------------------------------------#
    # check / open  file :
    #
    $infile = $directory . $infile;
    open( FILE, $infile ) || die ( "can't open file " . $infile . "\n" );
    @text1 = <FILE>;
    close(FILE);

#------------------------------------------------------------------------------#
    # searching last line:
    #
    $lines = $mxlnes + 1;
    while ( ( 0 <= $lines ) && ( !( @text1[$lines] ) ) ) {
        $lines--;
    }

    if ( $lines == -1 ) {
        die ( "The file " . $infile . " is void\n" );
    }
    elsif ( ( $output ne "STDOUT" ) && ( $lines <= $mxlnes ) ) {
        print $lines, " lines in " . $infile . ".\n";
    }
    elsif ( $mxlnes < $lines ) {
        print STDERR ( "too many lines [ N > maximum = ", $mxlnes,
          " ] in " . $directory . $infile . "!!!\n" );
    }

#------------------------------------------------------------------------------#
    # search last array index:
    #
    if ( $output ne "STDOUT" ) {

        #     print "Searching pattern [ ";
        print "please wait a moment ...";

        #     print " ]";
        print "\n";
    }
    if ( !( grep /$oldpattern/gc, @text1 ) ) {
        die ("No matches found\n");
    }
    elsif ( $output ne "STDOUT" ) {
        print "modifying file " . $infile . "\n";
    }

    $i = 0;
    while ( $i <= $lines ) {
        $text1[$i] =~ s/$oldpattern/$newpattern/gc;
        $i++;
    }

    if ( $output ne "STDOUT" ) {
        open( FILE, ">" . $output );
        print FILE (@text1);
        close(FILE);
        print "Done !\n";
    }
    else {
        print STDOUT (@text1);
    }
}
