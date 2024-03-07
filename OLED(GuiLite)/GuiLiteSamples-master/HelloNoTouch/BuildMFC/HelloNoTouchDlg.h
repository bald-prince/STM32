
// HelloNoTouchDlg.h : header file
//

#pragma once
extern "C" void startHelloNoTouch(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver);
extern "C" void sendTouch2HelloNoTouch(int x, int y, bool is_down);
extern "C" void sendKey2HelloNoTouch(unsigned int key);
extern void* getUiOfHelloNoTouch(int* width, int* height, bool force_update = false);

enum DISPLAY_MODE
{
	FRAME_BUFFER_MODE,
	EXTERNAL_GFX_MODE
};

typedef struct tagMYBITMAPINFO {
	BITMAPINFOHEADER    bmiHeader;
	DWORD				biRedMask;
	DWORD				biGreenMask;
	DWORD				biBlueMask;
} MYBITMAPINFO;

// CHelloNoTouchDlg dialog
class CHelloNoTouchDlg : public CDialogEx
{
// Construction
public:
	CHelloNoTouchDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HelloNoTouch_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

private:
	static void draw_pixel(int x, int y, unsigned int rgb);
	static void fill_rect(int x0, int y0, int x1, int y1, unsigned int rgb);
	static UINT ThreadHelloNoTouch(LPVOID pParam);
	static UINT ThreadRefreshUI(LPVOID pParam);
	static CHelloNoTouchDlg* m_the_dialog;
	static CRITICAL_SECTION m_criSection;

	void updateUI(CDC* pDC);

	CRect m_block_rect;
	int m_ui_width;
	int m_ui_height;
	int m_color_bytes = 2;
	CBitmap		m_blockBmp;
	MYBITMAPINFO m_ui_bm_info;
	CDC			m_memDC;

	DISPLAY_MODE m_display_mode = FRAME_BUFFER_MODE;
};
