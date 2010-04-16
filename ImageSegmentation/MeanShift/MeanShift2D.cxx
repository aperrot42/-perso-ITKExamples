#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkNumericTraits.h"

#include "itkThresholdImageFilter.h"

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
  
  // A threshold filter :
  typedef itk::ThresholdImageFilter< ImageType > ThresholdFilterType;


  //**********ARGUMENTS READING*********
  // We translate command line arguments to be interpreted by our example
  
  // We do a very basic check : does the user specify enough parameters :
  // 5 inputs ( program path, input_filename, and threshold_level low, 
  //            threshold_level high, output_filename )
  if ( argc != 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "(.exe) takes 3 arguments" <<std::endl;
    std::cerr <<"1- inputImageFile" <<std::endl;
    std::cerr <<"2- Thresold_level [0;255]" <<std::endl;
    std::cerr <<"3- output_filename" <<std::endl;
    return EXIT_FAILURE;
    }
  
  // We convert input arguments
  // Input filename
  const char* ArgInputFilename = argv[1]; //from string to string
  // Threshold levels
  PixelType ArgThresholdLevel = static_cast<PixelType> (atoi(argv[2]));  // string to PixelType
  // Output filename
  const char* ArgOutputFilename = argv[3];//from string to string
  
  // We display what the example will compute
  std::cout << "Thresholding " << ArgInputFilename
            << " at " << ArgThresholdLevel
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

  //**********THRESHOLD FILTERING**********
  // We simply connect the output of the reader to the input of the filter,
  // reader->Threshold_filter
  
  // Threshold filter creation :
  ThresholdFilterType::Pointer ThresholdFilter = ThresholdFilterType::New();
  
  //Threshold filter initialization
  ThresholdFilter->SetInput(Reader->GetOutput());
  
  ThresholdFilter->SetOutsideValue( itk::NumericTraits< PixelType >::Zero );
    
  // Threshold level setting
  ThresholdFilter->ThresholdBelow(ArgThresholdLevel);
  
  try 
    {
    ThresholdFilter->Update();
    }
  catch( itk::ExceptionObject & excp )  // If something goes wrong
    {
    std::cerr << "Problem while filtering" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }


	//*********WRITING OUTPUT IMAGE**********
  
  // Writer Creation :
	WriterType::Pointer Writer = WriterType::New();
  
  // Writer initialization (input and output)
	Writer->SetFileName( ArgOutputFilename );  // Threshold_filter->writer
	Writer->SetInput( ThresholdFilter->GetOutput());  // writer->Output_filename
  
  try
    {
	  Writer->Update();  // This update will update the whole pipeline
    }
  catch( itk::ExceptionObject & excp )  // If something goes wrong
    {
    std::cerr << "Problem writing the output file" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
