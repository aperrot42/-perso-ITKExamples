#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"

#include <iostream>

int main( int argc, char* argv[] )
{
  //**********TYPEDEF**********
  // Dimension of the image
  const unsigned Dimension = 2;
  // The type of manipulated pixels :
  typedef unsigned char PixelType;
  // The type of manipulated images :
  typedef itk::Image< PixelType, Dimension > ImageType;

  // A file reader (input) :
  typedef itk::ImageFileReader< ImageType > ReaderType;
  // A file writer (output) :
  typedef itk::ImageFileWriter< ImageType > WriterType;
  
  // A const iterator to read the input image
  typedef itk::ImageRegionConstIterator< ImageType > ConstIteratorType;
  // An iterator to write the output image
  typedef itk::ImageRegionIterator< ImageType >	IteratorType;  


  //**********ARGUMENTS READING*********
  // We translate command line arguments to be interpreted by our example
  
  // We do a very basic check : does the user specify enough parameters :
  // 4 inputs ( program path, input_filename, and threshold_level, output_filename )
  if ( argc != 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "(.exe) takes 3 arguments" <<std::endl;
    std::cerr <<"1- inputImageFile" <<std::endl;
    std::cerr <<"2- Thresold_level [0;255]" <<std::endl;
    std::cerr <<"3- output_filename" <<std::endl;
    return EXIT_FAILURE;
    }
  
  // We convert input arguments
  const char* ArgInputFilename = argv[1]; //from string to string
  //Threshold level
  PixelType ArgThresholdLevel = static_cast<PixelType> (atoi(argv[2]));
  const char* ArgOutputFilename = argv[3];
  
  // We display what the example will compute
  std::cout << "Thresholding " << ArgInputFilename
            << " at value " << ArgThresholdLevel
            << " output in " << ArgOutputFilename << std::endl;


  //**********INPUT IMAGE READING**********
  
  ReaderType::Pointer Reader = ReaderType::New();  //Create the reader
  
	Reader->SetFileName( ArgInputFilename ); // Set the reader input filename
  
  try // try to read the input file
    {
    Reader->Update();
    }
  catch( itk::ExceptionObject & excp )  // If something goes wrong
    {
    std::cerr << "Problem reading the input file" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }


  //TODO Here call the class

	//*********WRITING OUTPUT IMAGE**********
  
  // Writer Creation :
	WriterType::Pointer Writer = WriterType::New();
  
  // Writer initialization (input and output)
	Writer->SetFileName( "output.png" );
	Writer->SetInput( ImageOut);
  
  try
    {
	  Writer->Update();
    }
  catch( itk::ExceptionObject & excp )  // If something goes wrong
    {
    std::cerr << "Problem writing the output file" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
