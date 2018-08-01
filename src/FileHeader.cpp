#include "FileHeader.hpp"
#include "Incrementator.hpp"

using namespace Config;

FileHeader::FileHeader(WaveFile * pFile) {
  pFile_ = pFile;
  writeEmptyChunkSize();
  writeNoExtensionData();
  writePsmIntegerSamples();
  pFile_->writeToFile(numberOfChannels, 2 );  
  pFile_->writeToFile(samplesPerSecond, 4 );  
  writeBytesPerSecond(); 
  writeDataBlockSize(); 
  pFile_->writeToFile(bitsPerSample, 2 );  
}

void FileHeader::writeEmptyChunkSize() {
  pFile_->getFile() << "RIFF----WAVEfmt "; 
}

void FileHeader::writeNoExtensionData() {
  pFile_->writeToFile(16, 4 );  
}

void FileHeader::writePsmIntegerSamples() {
  pFile_->writeToFile(1, 2 );  
}

void FileHeader::writeBytesPerSecond() {
  pFile_->writeToFile(samplesPerSecond * bytesPerSample * numberOfChannels, 4 );  
}

void FileHeader::writeDataBlockSize() {
  pFile_->writeToFile(bytesPerSample * numberOfChannels, 2 ) ;  
}
	




