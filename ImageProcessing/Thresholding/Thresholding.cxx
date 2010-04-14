//==========================================================================
// Name        : ThresholdingITKex.cpp
// Author      : Antonin
// Version     : 0.1
//==========================================================================

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIterator.h>

#include <iostream>

int main(int argc, char* argv[])
  {

  //**********TYPEDEF**********
  // The type of manipulated pixels :
  typedef unsigned char PixelType;
  // The type of manipulated images :
  typedef itk::Image<PixelType,2> ImageType;

  // A file reader (input) :
  typedef itk::ImageFileReader< ImageType > ReaderType;
  // A file writer (output) :
  typedef itk::ImageFileWriter< ImageType > WriterType;
  
  // A const iterator to read the input image
  typedef itk::ImageRegionConstIterator<ImageType> ConstIteratorType;
  // An iterator to write the output image
  typedef itk::ImageRegionIterator<ImageType>	IteratorType;  


  //**********ARGUMENTS READING*********
  // We translate command line arguments to be interpreted by our example
  
  // We do a very basic check : does the user specify enough parameters :
  // 3 inputs ( program path, input_filename, and threshold_level)
  if ( argc != 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile Thresold_level(0-255)"
              << std::endl;
    return EXIT_FAILURE;
    }
  
  // We convert input arguments
  const char * ArgFilename = argv[1]; //from string to string
  //Threshold level
  const int ArgThresholdLevel = static_cast<PixelType> (atoi(argv[2]));
  
  // We display what the example will compute
  std::cout << "Thresholding " << ArgFilename
            << " at value " << ArgThresholdLevel
            << " output in output.png" << std::endl;


  //**********INPUT IMAGE READING**********
  
  ReaderType::Pointer Reader = ReaderType::New();  //Create the reader
  
	Reader->SetFileName( ArgFilename ); // Set the reader input filename
  
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


  //**********TEMPORARY STORING**********
  // We want to store the image in memory (ImageIn),
  // read it and create another image for the output.
  
  // The input image is the output of the reader
  ImageType::Pointer ImageIn = Reader->GetOutput(); // Input Image creation
  
  // Region definition :
  // we consider the whole image so we use the largest possible region
  ImageType::RegionType ImageRegion = ImageIn->GetLargestPossibleRegion();


  //**********OUTPUT ALLOCATION**********
  // First we have to describe the output, 
  // to be able to correctly allocate memory :

  // creation of the output image
  ImageType::Pointer ImageOut = ImageType::New(); 

  ImageOut->SetRegions( ImageRegion); //same region for input and output
  
  ImageOut->Allocate();// memory allocation for the output


  //**********DISPLAY INFORMATIONS**********
  // Display information about images in memory :

  // Display Input information
  std::cout << "**********INPUT IMAGE INFORATION**********" << std::endl
            << ImageIn << std::endl;
  // Display Output information
  std::cout << "**********OUTPUT IMAGE INFORATION**********" << std::endl
            << ImageOut << std::endl;


  //**********ITERATIONS ON IMAGE**********
  // After defining the iterator on the input and on the output,
  // We go across the whole image
  
  //iterators creation :
  // Constant iterator on input image :
  ConstIteratorType ItIn( ImageIn,	ImageIn->GetBufferedRegion());
  // Iterator on output image :
  IteratorType ItOut( ImageOut, ImageOut->GetBufferedRegion());

  // image scan loop:
  // while the input iterator is in the considered region
  PixelType CurrentPixel;
  while( !ItIn.IsAtEnd() )
    {
    CurrentPixel = ItIn.Get(); // read input and store it in current pixel
      if (CurrentPixel< ArgThresholdLevel)
        {
        ItOut.Set(CurrentPixel);
        }
    ++ItIn;  // next input pixel
	  ++ItOut;  // next output pixel
    }

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
  }


