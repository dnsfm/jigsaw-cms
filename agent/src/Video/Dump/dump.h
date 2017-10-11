class CDumpInputPin;
class CDump;
class CDumpFilter;


// Main filter object

class CDumpFilter : public CBaseFilter
{
    CDump * const m_pDump;

public:

    // Constructor
    CDumpFilter(CDump *pDump,
                LPUNKNOWN pUnk,
                CCritSec *pLock,
                HRESULT *phr);

    // Pin enumeration
    CBasePin * GetPin(int n);
    int GetPinCount();

    // Open and close the file as necessary
    STDMETHODIMP Run(REFERENCE_TIME tStart);
    STDMETHODIMP Pause();
    STDMETHODIMP Stop();
};


//  Pin object

class CDumpInputPin : public CRenderedInputPin
{
    CDump    * const m_pDump;           // Main renderer object
    CCritSec * const m_pReceiveLock;    // Sample critical section
    REFERENCE_TIME m_tLast;             // Last sample receive time

public:

    CDumpInputPin(CDump *pDump,
                  LPUNKNOWN pUnk,
                  CBaseFilter *pFilter,
                  CCritSec *pLock,
                  CCritSec *pReceiveLock,
                  HRESULT *phr);

    // Do something with this media sample
    STDMETHODIMP Receive(IMediaSample *pSample);
    STDMETHODIMP EndOfStream(void);
    STDMETHODIMP ReceiveCanBlock();

    // Check if the pin can support this specific proposed type and format
    HRESULT CheckMediaType(const CMediaType *);

    // Break connection
    HRESULT BreakConnect();

    // Track NewSegment
    STDMETHODIMP NewSegment(REFERENCE_TIME tStart,
                            REFERENCE_TIME tStop,
                            double dRate);
};


//  CDump object which has filter and pin members

class CDump : public CUnknown, public IFileSinkFilter, public ISetVideoCaptureCallback
{
    friend class CDumpFilter;
    friend class CDumpInputPin;

    CDumpFilter   *m_pFilter;       // Methods for filter interfaces
    CDumpInputPin *m_pPin;          // A simple rendered input pin

    CCritSec m_Lock;                // Main renderer critical section
    CCritSec m_ReceiveLock;         // Sublock for received samples

    LPOLESTR m_pFileName;           // The filename where we dump

	VIDEOCAPTURE_CALLBACK m_pCallback; 	// Capture call back function.
	void* m_pCallbackParameter;         // Capture call back parameter.

	bool m_IsClip;       // �Ƿ�ü�
	int m_ClipWidth;     // �ü�֮ǰ�Ŀ��
	int m_ClipHeight;    // �ü�֮ǰ�ĸ߶�

public:

    DECLARE_IUNKNOWN

    CDump(LPUNKNOWN pUnk, HRESULT *phr);
    ~CDump();

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    // Implements the IFileSinkFilter interface
    STDMETHODIMP SetFileName(LPCOLESTR pszFileName,const AM_MEDIA_TYPE *pmt);
    STDMETHODIMP GetCurFile(LPOLESTR * ppszFileName,AM_MEDIA_TYPE *pmt);

	// Implements the ISetVideoCaptureCallback interface
	STDMETHODIMP  SetCallback(VIDEOCAPTURE_CALLBACK pCallback, void* pCallbackParameter);
	STDMETHODIMP  SetClip(unsigned int width, unsigned int height);

private:

    // Overriden to say what interfaces we support where
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);
};

