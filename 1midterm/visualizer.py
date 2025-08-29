"""
Autor: Oscar Vargas Pabon
Para visualizar eso
"""
from PIL import Image
import sys

assert len(sys.argv)>=2;

in_file_path = sys.argv[1]

#type="?????????????"
#if( ".ppm" in in_file_path ): type="ppm";
#elif(".pgm" in in_file_path): type="pgm";
png_file_path = in_file_path[:-4]+".png"  # Desired output PNG file

try:
    with Image.open(in_file_path) as img:
        img.save(png_file_path)
except FileNotFoundError:
    print(f"Error: PPM file not found at '{in_file_path}'")
except Exception as e:
    print(f"An error occurred during conversion: {e}")