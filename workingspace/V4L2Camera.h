#ifndef V4L2Camera_hh
#define V4L2Camera_hh

#include <linux/videodev2.h>
#include <libv4l2.h>
#include <sys/time.h>
#include <string>

class V4L2Camera {
public:

  struct DataBuffer {
    void   *data;
    size_t length;
    size_t width;
    size_t height;
  };

  enum ImageSize {
    SIZE_640_480 = 0,
    SIZE_320_240,
    SIZE_160_120
  };

  /**
   * Constructor which will allocate memory
   */
  V4L2Camera();

  /**
   * Destructor which will call disconnect and free up memory
   */
  ~V4L2Camera();

  /**
   * Connect to the camera and set it up for grabbing images
   *
   * @param device the device name (default /dev/video0
   * @return true if we could open the device
   */
  bool connect(const std::string &device = "/dev/video0");

  /**
   * @param is desired image size
   * @param numBuffers we can use a number of buffers to read the
   * image data inte. This means that we can start grabbing the data
   * for a new frame before we have processed the previous one and
   * still not overwrite the previous one.
   * @return true if initialization succeeded
   */
  bool init(enum ImageSize is=SIZE_160_120, int numBuffers = 2);

  /**
   * Disconnect from the camera device
   */
  void disconnect();

  /**
   * @return the number of buffers used to store data
   */
  int getNumBuffers() const { return m_NumDataBuffers; }

  /**
   * This function will grab an image which will be stored in the
   * buffer. The function returns the index into this buffer.
   *
   * @return index into the buffers with data, this should be
   * 0-(getNumBuffers()-1). In case of errors this function returns a
   * negative number.
   */
  int grabBlocking(double maxSecs = 2);

  /**
   * @return pointer to the data buffer with a certain index
   */
  DataBuffer* getDataBuffer(int index) { return m_DataBuffers + index; }

  /**
   * Use this function to write the image data to a PPM file
   * @param index the image index in the buffer (returned by grabImageBlocking)
   * @param filename the name of the file to write the image to
   * @return true if written ok
   */
  bool writeBufferToPPM(int index, const std::string &filename);

private:

  bool init(unsigned int width, unsigned int height, int numBuffers = 2);

  /**
   * @return true if OK
   */
  bool sendIoctlRequest(unsigned long int request, void *arg);

  inline double getCurrentTime()
  {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1.0*tv.tv_sec + 1e-6*tv.tv_usec);
  }

  int m_Fd;
  struct v4l2_format m_Format;
  struct v4l2_buffer m_Buffer;
  struct v4l2_requestbuffers m_ReqBuffer;
  enum v4l2_buf_type m_Type;

  int m_NumDataBuffers;
  struct DataBuffer *m_DataBuffers;
};


#endif // V4L2Camera_hh
