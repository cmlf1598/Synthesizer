// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.h
//
/**
    \file   plugincore.h
    \author Will Pirkle
    \date   17-September-2018
    \brief  base class interface file for ASPiK plugincore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#ifndef __pluginCore_h__
#define __pluginCore_h__

#include "pluginbase.h"

// **--0x7F1F--**

// --- Plugin Variables controlID Enumeration 

enum controlID {
	a1_ff_filter_gui = 0,
	volume_gui = 1,
	a0_ff_filter_gui = 10,
	a0_fb_filter_gui = 20,
	filter_selection_gui = 40,
	frequency_osc_gui = 2,
	start_osc_gui = 12,
	b1_fb_filter_gui = 30,
	osc_type_gui = 22
};

	// **--0x0F1F--**

/**
\class PluginCore
\ingroup ASPiK-Core
\brief
The PluginCore object is the default PluginBase derived object for ASPiK projects.
Note that you are fre to change the name of this object (as long as you change it in the compiler settings, etc...)


PluginCore Operations:
- overrides the main processing functions from the base class
- performs reset operation on sub-modules
- processes audio
- processes messages for custom views
- performs pre and post processing functions on parameters and audio (if needed)

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class PluginCore : public PluginBase
{
public:
    PluginCore();

	/** Destructor: empty in default version */
    virtual ~PluginCore(){}

	// --- PluginBase Overrides ---
	//
	/** this is the creation function for all plugin parameters */
	bool initPluginParameters();

	/** called when plugin is loaded, a new audio file is playing or sample rate changes */
	virtual bool reset(ResetInfo& resetInfo);

	/** one-time post creation init function; pluginInfo contains path to this plugin */
	virtual bool initialize(PluginInfo& _pluginInfo);

	// --- preProcess: sync GUI parameters here; override if you don't want to use automatic variable-binding
	virtual bool preProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** process frames of data */
	virtual bool processAudioFrame(ProcessFrameInfo& processFrameInfo);

	// --- uncomment and override this for buffer processing; see base class implementation for
	//     help on breaking up buffers and getting info from processBufferInfo
	//virtual bool processAudioBuffers(ProcessBufferInfo& processBufferInfo);

	/** preProcess: do any post-buffer processing required; default operation is to send metering data to GUI  */
	virtual bool postProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo);

	/** this can be called: 1) after bound variable has been updated or 2) after smoothing occurs  */
	virtual bool postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** this is ony called when the user makes a GUI control change */
	virtual bool guiParameterChanged(int32_t controlID, double actualValue);

	/** processMessage: messaging system; currently used for custom/special GUI operations */
	virtual bool processMessage(MessageInfo& messageInfo);

	/** processMIDIEvent: MIDI event processing */
	virtual bool processMIDIEvent(midiEvent& event);

	/** specialized joystick servicing (currently not used) */
	virtual bool setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData);

	/** create the presets */
	bool initPluginPresets();

	// --- BEGIN USER VARIABLES AND FUNCTIONS -------------------------------------- //
	//	   Add your variables and methods here

	//Feed-Forward Filter variables
	double a0_left_ff_filter;
	double a0_right_ff_filter;
	
	double a1_left_ff_filter;
	double a1_right_ff_filter;

	double z1_left_ff_filter;
	double z1_right_ff_filter;

	//Feed-back Filter variables
	double a0_left_fb_filter;
	double a0_right_fb_filter;
	
	double b1_left_fb_filter;
	double b1_right_fb_filter;

	double z1_left_fb_filter;
	double z1_right_fb_filter;

	//Oscillator
	//
	// array for the table
	double sin_array[1024];			// 1024 Point Sinusoid 
	double saw_tooth_array[1024];	// saw
	double triangle_array[1024];	// tri
	double square_array[1024];		// sqr

	// current read location
	double read_index;	

	// reset the read index
	void reset()
	{
		read_index = 0.0;
	}

	// increment value
	double inc;

	// linear interpolation 
	double linear_interpolation(double x1, double x2, double y1, double y2, double frac);

	//Direct Oscillator

	////coefficients, 2nd Order FB
	//double b1_osc;
	//double b2_osc;

	////delay elements, 2nd Order FB
	//double y_z1_osc;
	//double y_z2_osc;

	//function to cook frequency and set initial conditions
	void cook_frequency();

	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //

private:
	//  **--0x07FD--**

	// --- Continuous Plugin Variables 
	double a1_ff_filter_gui = 0.0;
	double volume_gui = 0.0;
	double a0_ff_filter_gui = 0.0;
	double a0_fb_filter_gui = 0.0;
	double frequency_osc_gui = 0.0;
	double b1_fb_filter_gui = 0.0;

	// --- Discrete Plugin Variables 
	int filter_selection_gui = 0;
	enum class filter_selection_guiEnum { FF_Filter,FB_Filter };	// to compare: if(compareEnumToInt(filter_selection_guiEnum::FF_Filter, filter_selection_gui)) etc... 

	int start_osc_gui = 0;
	enum class start_osc_guiEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(start_osc_guiEnum::SWITCH_OFF, start_osc_gui)) etc... 

	int osc_type_gui = 0;
	enum class osc_type_guiEnum { sine,saw,tri,square };	// to compare: if(compareEnumToInt(osc_type_guiEnum::sine, osc_type_gui)) etc... 

	// **--0x1A7F--**
    // --- end member variables

public:
    /** static description: bundle folder name

	\return bundle folder name as a const char*
	*/
    static const char* getPluginBundleName();

    /** static description: name

	\return name as a const char*
	*/
    static const char* getPluginName();

	/** static description: short name

	\return short name as a const char*
	*/
	static const char* getShortPluginName();

	/** static description: vendor name

	\return vendor name as a const char*
	*/
	static const char* getVendorName();

	/** static description: URL

	\return URL as a const char*
	*/
	static const char* getVendorURL();

	/** static description: email

	\return email address as a const char*
	*/
	static const char* getVendorEmail();

	/** static description: Cocoa View Factory Name

	\return Cocoa View Factory Name as a const char*
	*/
	static const char* getAUCocoaViewFactoryName();

	/** static description: plugin type

	\return type (FX or Synth)
	*/
	static pluginType getPluginType();

	/** static description: VST3 GUID

	\return VST3 GUID as a const char*
	*/
	static const char* getVSTFUID();

	/** static description: 4-char code

	\return 4-char code as int
	*/
	static int32_t getFourCharCode();

	/** initalizer */
	bool initPluginDescriptors();

};




#endif /* defined(__pluginCore_h__) */
