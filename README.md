# What is it?

gpxpp is a C++23 based library to read and manipulate .gpx files.

# Capabilities
At this moment the library allows you to load a given .gpx file into a library's Document type.
This document holds all tracks in the given .gpx file, each track is then composed of one or more segments.
Finally a segment is holds each recorded point that consists of the latitude, longitude, elevation and timestamp.

At this moment, the library offers a few algorithms to alter the gpx data. The main ones are the possibility to calculate
the total distance of a range of points. However the libeary provides functions that accept not only a range of points,
but also the document itself, a track, segment or even just range of a few selected points.
Another function of the library is the ability to calaulate the elevation gain or loss of a range of points.
Similarily you're not constrained to only a range of points but can execute this calculation using the document instance or track etc...

The library's types offer methods to get a range of all the underlying points. This is done by flattening all of the points into one range.
The separation of tracks/segments does not exist in such a range so be careful when using such range to compute the distances, elevation gains and losses or other metrics.
