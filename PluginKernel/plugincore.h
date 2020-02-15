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
	volume_osc_1_gui = 11,
	frequency_osc_1_gui = 12,
	start_osc_1_gui = 10,
	osc_1_type_gui = 13,
	osc_1_mode_gui = 14,
	start_osc_2_gui = 20,
	frequency_osc_2_gui = 22,
	osc_2_type_gui = 23,
	osc_2_mode_gui = 24,
	volume_osc_2_gui = 21
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

	//Oscillators
	//
	// arrays for the tables
	double sin_array[1024];			// 1024 Point Sinusoid 
	double saw_tooth_array[1024];	// saw
	double triangle_array[1024];	// tri
	double square_array[1024];		// sqr

	// band limited to the 5th harmonic
	double saw_tooth_array_bl5[1024];
	double triangle_array_bl5[1024];
	double square_array_bl5[1024];

	// current read locations
	double read_index_osc_1;	
	double read_index_osc_2;

	// reset the read indexes
	void reset()
	{
		read_index_osc_1 = 0.0;
		read_index_osc_2 = 0.0;
	}

	// increment values
	double inc_osc_1;
	double inc_osc_2;

	// linear interpolation 
	double linear_interpolation(double x1, double x2, double y1, double y2, double frac);

	//function to cook frequency and set initial conditions
	void cook_frequency_osc_1();
	void cook_frequency_osc_2();

	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //

private:
	//  **--0x07FD--**

	// --- Continuous Plugin Variables 
	double volume_osc_1_gui = 0.0;
	double frequency_osc_1_gui = 0.0;
	double frequency_osc_2_gui = 0.0;
	double volume_osc_2_gui = 0.0;

	// --- Discrete Plugin Variables 
	int start_osc_1_gui = 0;
	enum class start_osc_1_guiEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(start_osc_1_guiEnum::SWITCH_OFF, start_osc_1_gui)) etc... 

	int osc_1_type_gui = 0;
	enum class osc_1_type_guiEnum { sine,saw,tri,square };	// to compare: if(compareEnumToInt(osc_1_type_guiEnum::sine, osc_1_type_gui)) etc... 

	int osc_1_mode_gui = 0;
	enum class osc_1_mode_guiEnum { normal,bandlimited };	// to compare: if(compareEnumToInt(osc_1_mode_guiEnum::normal, osc_1_mode_gui)) etc... 

	int start_osc_2_gui = 0;
	enum class start_osc_2_guiEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(start_osc_2_guiEnum::SWITCH_OFF, start_osc_2_gui)) etc... 

	int osc_2_type_gui = 0;
	enum class osc_2_type_guiEnum { sine,saw,tri,square };	// to compare: if(compareEnumToInt(osc_2_type_guiEnum::sine, osc_2_type_gui)) etc... 

	int osc_2_mode_gui = 0;
	enum class osc_2_mode_guiEnum { normal,bandlimited };	// to compare: if(compareEnumToInt(osc_2_mode_guiEnum::normal, osc_2_mode_gui)) etc... 

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
