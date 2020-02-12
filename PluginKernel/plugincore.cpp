// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.cpp
//
/**
    \file   plugincore.cpp
    \author Will Pirkle
    \date   17-September-2018
    \brief  Implementation file for PluginCore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#include "plugincore.h"
#include "plugindescription.h"

/**
\brief PluginCore constructor is launching pad for object initialization

Operations:
- initialize the plugin description (strings, codes, numbers, see initPluginDescriptors())
- setup the plugin's audio I/O channel support
- create the PluginParameter objects that represent the plugin parameters (see FX book if needed)
- create the presets
*/
PluginCore::PluginCore()
{
    // --- describe the plugin; call the helper to init the static parts you setup in plugindescription.h
    initPluginDescriptors();

    // --- default I/O combinations
	// --- for FX plugins
	if (getPluginType() == kFXPlugin)
	{
		addSupportedIOCombination({ kCFMono, kCFMono });
		addSupportedIOCombination({ kCFMono, kCFStereo });
		addSupportedIOCombination({ kCFStereo, kCFStereo });
	}
	else // --- synth plugins have no input, only output
	{
		addSupportedIOCombination({ kCFNone, kCFMono });
		addSupportedIOCombination({ kCFNone, kCFStereo });
	}

	// --- for sidechaining, we support mono and stereo inputs; auxOutputs reserved for future use
	addSupportedAuxIOCombination({ kCFMono, kCFNone });
	addSupportedAuxIOCombination({ kCFStereo, kCFNone });

	// --- create the parameters
    initPluginParameters();

    // --- create the presets
    initPluginPresets();
}

/**
\brief create all of your plugin parameters here

\return true if parameters were created, false if they already existed
*/
bool PluginCore::initPluginParameters()
{
	if (pluginParameterMap.size() > 0)
		return false;

    // --- Add your plugin parameter instantiation code bewtween these hex codes
	// **--0xDEA7--**


	// --- Declaration of Plugin Parameter Objects 
	PluginParameter* piParam = nullptr;

	// --- continuous control: FF Filter a1
	piParam = new PluginParameter(controlID::a1_ff_filter_gui, "FF Filter a1", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&a1_ff_filter_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Volume
	piParam = new PluginParameter(controlID::volume_gui, "Volume", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.707000, taper::kAntiLogTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&volume_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FF Filter a0
	piParam = new PluginParameter(controlID::a0_ff_filter_gui, "FF Filter a0", "", controlVariableType::kDouble, -1.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&a0_ff_filter_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: FB Filter a0
	piParam = new PluginParameter(controlID::a0_fb_filter_gui, "FB Filter a0", "", controlVariableType::kDouble, -1.000000, 1.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&a0_fb_filter_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Filter selection
	piParam = new PluginParameter(controlID::filter_selection_gui, "Filter selection", "FF Filter,FB Filter", "FF Filter");
	piParam->setBoundVariable(&filter_selection_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Frequency
	piParam = new PluginParameter(controlID::frequency_osc_gui, "Frequency", "Hz", controlVariableType::kDouble, 25.000000, 4200.000000, 440.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&frequency_osc_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Start Osc
	piParam = new PluginParameter(controlID::start_osc_gui, "Start Osc", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&start_osc_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: FB Filter b1
	piParam = new PluginParameter(controlID::b1_fb_filter_gui, "FB Filter b1", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&b1_fb_filter_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Osc Type
	piParam = new PluginParameter(controlID::osc_type_gui, "Osc Type", "sine,saw,tri,square", "sine");
	piParam->setBoundVariable(&osc_type_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::a1_ff_filter_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483703);
	setParamAuxAttribute(controlID::a1_ff_filter_gui, auxAttribute);

	// --- controlID::volume_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483702);
	setParamAuxAttribute(controlID::volume_gui, auxAttribute);

	// --- controlID::a0_ff_filter_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483703);
	setParamAuxAttribute(controlID::a0_ff_filter_gui, auxAttribute);

	// --- controlID::a0_fb_filter_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483703);
	setParamAuxAttribute(controlID::a0_fb_filter_gui, auxAttribute);

	// --- controlID::filter_selection_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::filter_selection_gui, auxAttribute);

	// --- controlID::frequency_osc_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483680);
	setParamAuxAttribute(controlID::frequency_osc_gui, auxAttribute);

	// --- controlID::start_osc_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::start_osc_gui, auxAttribute);

	// --- controlID::b1_fb_filter_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483703);
	setParamAuxAttribute(controlID::b1_fb_filter_gui, auxAttribute);

	// --- controlID::osc_type_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::osc_type_gui, auxAttribute);


	// **--0xEDA5--**
   
    // --- BONUS Parameter
    // --- SCALE_GUI_SIZE
    PluginParameter* piParamBonus = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
    addPluginParameter(piParamBonus);

	// --- create the super fast access array
	initPluginParameterArray();

    return true;
}

/**
\brief initialize object for a new run of audio; called just before audio streams

Operation:
- store sample rate and bit depth on audioProcDescriptor - this information is globally available to all core functions
- reset your member objects here

\param resetInfo structure of information about current audio format

\return true if operation succeeds, false otherwise
*/
bool PluginCore::reset(ResetInfo& resetInfo)
{
    // --- save for audio processing
    audioProcDescriptor.sampleRate = resetInfo.sampleRate;
    audioProcDescriptor.bitDepth = resetInfo.bitDepth;

    // --- other reset inits
    return PluginBase::reset(resetInfo);
}

/**
\brief one-time initialize function called after object creation and before the first reset( ) call

Operation:
- saves structure for the plugin to use; you can also load WAV files or state information here
*/
bool PluginCore::initialize(PluginInfo& pluginInfo)
{
	// --- add one-time init stuff here
	
	//Filters

	//Feed-Forward Filter setup
	a0_left_ff_filter = a0_ff_filter_gui;
	a0_right_ff_filter = a0_ff_filter_gui;

	a1_left_ff_filter = a1_ff_filter_gui;
	a1_right_ff_filter = a1_ff_filter_gui;

	z1_left_ff_filter = 0.0;
	z1_right_ff_filter = 0.0;

	//Feed-Back Filter initialization
	a0_left_fb_filter = a0_fb_filter_gui;
	a0_right_fb_filter = a0_fb_filter_gui;

	b1_left_fb_filter = b1_fb_filter_gui;
	b1_right_fb_filter = b1_fb_filter_gui;

	z1_left_fb_filter = 0.0;
	z1_right_fb_filter = 0.0;

	//Wave Table Oscillators

	//Triangle wave
	// slope and y-intercept values.
	// rising edge 1:
	double m1_tri_r = 1.0 / 256.0;
	double b1_tri_r = 0.0;

	// rising edge 2:
	double m2_tri_r = 1.0 / 256.0;
	double b2_tri_r = - 1.0;

	// falling edge:
	double m1_tri_f = -2.0 / 512.0;
	double b1_tri_f = + 1.0;

	// Sawtooth
	// rising edge 1:
	double m1_saw_r = 1.0 / 512.0;
	double b1_saw_r = 0.0;

	// rising edge 2:
	double m2_saw_r = 1.0 / 512.0;
	double b2_saw_r = -1.0;


	for (int i = 0; i < 1024; i++)
	{
		// sample the sinusoid. 1024 points
		// sin(wnT) = sin(2pi*i/1024)
		sin_array[i] = sin(((double) (i/ 1024.0) )* (kTwoPi));

		// Sawtooth
		saw_tooth_array[i] = i < 512 ? m1_saw_r * i + b1_saw_r : m2_saw_r * ((__int64)i - 511) + b2_saw_r;

		// Triangle 
		if (i < 256)
			triangle_array[i] = m1_tri_r * i + b1_tri_r;
		else if (i >= 256 && i < 768)
			triangle_array[i] = m1_tri_f * ((__int64)i - 256) + b1_tri_f;
		else
			triangle_array[i] = m2_tri_r * ((__int64)i - 768) + b2_tri_r;

		// Square
		square_array[i] = i < 512 ? +1.0 : -1.0;

	}

	// clear variables 
	read_index = 0.0;
	inc = 0.0;

	//b1_osc = 0;
	//b2_osc = 0;

	//y_z1_osc = 0;
	//y_z2_osc = 0;

	// initialize inc
	cook_frequency();

	return true;
}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- syncInBoundVariables when preProcessAudioBuffers is called, it is *guaranteed* that all GUI control change information
  has been applied to plugin parameters; this binds parameter changes to your underlying variables
- NOTE: postUpdatePluginParameter( ) will be called for all bound variables that are acutally updated; if you need to process
  them individually, do so in that function
- use this function to bulk-transfer the bound variable data into your plugin's member object variables

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::preProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
    // --- sync internal variables to GUI parameters; you can also do this manually if you don't
    //     want to use the auto-variable-binding
    syncInBoundVariables();

	//reset the index
	//reset();

	//cook current frequency
	//cook_frequency();

    return true;
}

/**
\brief frame-processing method

Operation:
- decode the plugin type - for synth plugins, fill in the rendering code; for FX plugins, delete the if(synth) portion and add your processing code
- note that MIDI events are fired for each sample interval so that MIDI is tightly sunk with audio
- doSampleAccurateParameterUpdates will perform per-sample interval smoothing

\param processFrameInfo structure of information about *frame* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioFrame(ProcessFrameInfo& processFrameInfo)
{
    // --- fire any MIDI events for this sample interval
    processFrameInfo.midiEventQueue->fireMidiEvents(processFrameInfo.currentFrame);

	// --- do per-frame updates; VST automation and parameter smoothing
	doSampleAccurateParameterUpdates();

	//variables can go here.

	//Oscillator
	//double yn_osc;
	double out_sample;
	int int_read_index;
	double frac_read_index;
	int int_read_index_next;

	//Feed-Forward Filter 
	double xn_left_ff_filter;
	double xn_1_left_ff_filter;
	double yn_left_ff_filter;

	double xn_right_ff_filter;
	double xn_1_right_ff_filter;
	double yn_right_ff_filter;

	//Feed-Back Filter 
	double xn_left_fb_filter;
	double yn_left_fb_filter;
	double yn_1_left_fb_filter;

	double xn_right_fb_filter;
	double yn_right_fb_filter;
	double yn_1_right_fb_filter;

	//Volume
	double master_volume_left = volume_gui;
	double master_volume_right = volume_gui;

    // --- decode the channelIOConfiguration and process accordingly
    //
	// --- Synth Plugin:
	// --- Synth Plugin --- remove for FX plugins

	if (getPluginType() == kSynthPlugin)
	{
		// --- output silence: change this with your signal render code
		if (start_osc_gui == 0) 
		{
			processFrameInfo.audioOutputFrame[0] = 0.0;
			if (processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
				processFrameInfo.audioOutputFrame[1] = 0.0;

			return true;	/// processed
		}

		//Oscillator
		//yn_osc = -b1_osc * y_z1_osc - b2_osc * y_z2_osc;

		// output value for this cycle
		out_sample = 0;

		// get integer part
		int_read_index = (int) read_index;

		//get fractional part
		frac_read_index = read_index - (double) int_read_index;

		//second index for interpolation: wrap around buffer if needed
		int_read_index_next = int_read_index + 1 > 1023 ? 0 : int_read_index + 1;

		// interpolate the output

		if (compareEnumToInt(osc_type_guiEnum::sine, osc_type_gui)) 
			//sine
			out_sample = linear_interpolation(0.0, 1.0, sin_array[int_read_index], sin_array[int_read_index_next], frac_read_index);
		else if (compareEnumToInt(osc_type_guiEnum::saw, osc_type_gui))
			//saw
			out_sample = linear_interpolation(0.0, 1.0, saw_tooth_array[int_read_index], saw_tooth_array[int_read_index_next], frac_read_index);
		else if (compareEnumToInt(osc_type_guiEnum::tri, osc_type_gui))
			//triangular
			out_sample = linear_interpolation(0.0, 1.0, triangle_array[int_read_index], triangle_array[int_read_index_next], frac_read_index);
		else if (compareEnumToInt(osc_type_guiEnum::square, osc_type_gui))
			//square
			out_sample = linear_interpolation(0.0, 1.0, square_array[int_read_index], square_array[int_read_index_next], frac_read_index);

		// add increment 
		read_index += inc;

		//check the wrap
		if (read_index > 1024.0)
			read_index = read_index - 1024.0;

		//write out
		processFrameInfo.audioOutputFrame[0] = master_volume_left*out_sample;
		if (processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
			processFrameInfo.audioOutputFrame[1] = master_volume_right*out_sample;

		return true;	/// processed

		//update oscillator memory blocks
		//y_z2_osc = y_z1_osc;
		//y_z1_osc = yn_osc;
	}



	

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing

		//Feed-Forward Filter 

		if (compareEnumToInt(filter_selection_guiEnum::FF_Filter, filter_selection_gui)) 
		{
			// Input sample is x(n)
			xn_left_ff_filter = processFrameInfo.audioInputFrame[0];

			//Delay sample is x(n - 1)
			xn_1_left_ff_filter = z1_left_ff_filter;

			//Difference Equation
			yn_left_ff_filter = a0_left_ff_filter * xn_left_ff_filter + a1_left_ff_filter * xn_1_left_ff_filter;

			//Delay with current x(n)
			z1_left_ff_filter = xn_left_ff_filter;

			//Output sample is y(n)
			processFrameInfo.audioOutputFrame[0] = yn_left_ff_filter * master_volume_left;
		}

		//Feed-back Filter 

		if (compareEnumToInt(filter_selection_guiEnum::FB_Filter, filter_selection_gui))
		{
			// Input sample is x(n)
			xn_left_fb_filter = processFrameInfo.audioInputFrame[0];

			//Delay sample is y(n - 1)
			yn_1_left_fb_filter = z1_left_fb_filter;

			//Difference Equation
			yn_left_fb_filter = a0_left_fb_filter * xn_left_fb_filter - b1_left_fb_filter * yn_1_left_fb_filter;

			//Delay with current y(n)
			z1_left_fb_filter = yn_left_fb_filter;

			//Output sample is y(n)
			processFrameInfo.audioOutputFrame[0] = yn_left_fb_filter * master_volume_left;
		}

        return true; /// processed
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing

		//Feed-Forward Filter 

		if (compareEnumToInt(filter_selection_guiEnum::FF_Filter, filter_selection_gui))
		{
			// Input sample is x(n)
			xn_left_ff_filter = processFrameInfo.audioInputFrame[0];

			//Delay sample is x(n - 1)
			xn_1_left_ff_filter = z1_left_ff_filter;

			//Difference Equation
			yn_left_ff_filter = a0_left_ff_filter * xn_left_ff_filter + a1_left_ff_filter * xn_1_left_ff_filter;

			//Delay with current x(n)
			z1_left_ff_filter = xn_left_ff_filter;

			//Output sample is y(n)
			yn_right_ff_filter = yn_left_ff_filter;
			processFrameInfo.audioOutputFrame[0] = yn_left_ff_filter * master_volume_left;
			processFrameInfo.audioOutputFrame[1] = yn_right_ff_filter * master_volume_right;
		}

		//Feed-back Filter 

		if (compareEnumToInt(filter_selection_guiEnum::FB_Filter, filter_selection_gui))
		{
			// Input sample is x(n)
			xn_left_fb_filter = processFrameInfo.audioInputFrame[0];

			//Delay sample is y(n - 1)
			yn_1_left_fb_filter = z1_left_fb_filter;

			//Difference Equation
			yn_left_fb_filter = a0_left_fb_filter * xn_left_fb_filter - b1_left_fb_filter * yn_1_left_fb_filter;

			//Delay with current y(n)
			z1_left_fb_filter = yn_left_fb_filter;

			//Output sample is y(n)
			yn_right_fb_filter = yn_left_fb_filter;
			processFrameInfo.audioOutputFrame[0] = yn_left_fb_filter * master_volume_left;
			processFrameInfo.audioOutputFrame[1] = yn_right_fb_filter * master_volume_right;
		}

		return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing

		//Feed-Forward Filter 

		if (compareEnumToInt(filter_selection_guiEnum::FF_Filter, filter_selection_gui))
		{
			// Input sample is x(n)
			xn_left_ff_filter = processFrameInfo.audioInputFrame[0];
			xn_right_ff_filter = processFrameInfo.audioInputFrame[1];

			//Delay sample is x(n - 1)
			xn_1_left_ff_filter = z1_left_ff_filter;
			xn_1_right_ff_filter = z1_right_ff_filter;

			//Difference Equation
			yn_left_ff_filter = a0_left_ff_filter * xn_left_ff_filter + a1_left_ff_filter * xn_1_left_ff_filter;
			yn_right_ff_filter = a0_right_ff_filter * xn_right_ff_filter + a1_right_ff_filter * xn_1_right_ff_filter;

			//Delay with current x(n)
			z1_left_ff_filter = xn_left_ff_filter;
			z1_right_ff_filter = xn_right_ff_filter;

			//Output sample is y(n)
			processFrameInfo.audioOutputFrame[0] = yn_left_ff_filter * master_volume_left;
			processFrameInfo.audioOutputFrame[1] = yn_right_ff_filter * master_volume_right;
		}

		if (compareEnumToInt(filter_selection_guiEnum::FB_Filter, filter_selection_gui))
		{
			// Input sample is x(n)
			xn_left_fb_filter = processFrameInfo.audioInputFrame[0];
			xn_right_fb_filter = processFrameInfo.audioInputFrame[1];

			//Delay sample is y(n - 1)
			yn_1_left_fb_filter = z1_left_fb_filter;
			yn_1_right_fb_filter = z1_right_fb_filter;

			//Difference Equation
			yn_left_fb_filter = a0_left_fb_filter * xn_left_fb_filter - b1_left_fb_filter * yn_1_left_fb_filter;
			yn_right_fb_filter = a0_right_fb_filter * xn_right_fb_filter - b1_right_fb_filter * yn_1_right_fb_filter;

			//Delay with current y(n)
			z1_left_fb_filter = yn_left_fb_filter;
			z1_right_fb_filter = yn_right_fb_filter;

			//Output sample is y(n)
			processFrameInfo.audioOutputFrame[0] = yn_left_fb_filter * master_volume_left;
			processFrameInfo.audioOutputFrame[1] = yn_right_fb_filter * master_volume_right;
		}

        return true; /// processed
    }

    return false; /// NOT processed
}


/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- updateOutBoundVariables sends metering data to the GUI meters

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
	// --- update outbound variables; currently this is meter data only, but could be extended
	//     in the future
	updateOutBoundVariables();

    return true;
}

/**
\brief update the PluginParameter's value based on GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- use base class helper
    setPIParamValue(controlID, controlValue);

    // --- do any post-processing
    postUpdatePluginParameter(controlID, controlValue, paramInfo);

    return true; /// handled
}

/**
\brief update the PluginParameter's value based on *normlaized* GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param normalizedValue the new control value in normalized form
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo)
{
	// --- use base class helper, returns actual value
	double controlValue = setPIParamValueNormalized(controlID, normalizedValue, paramInfo.applyTaper);

	// --- do any post-processing
	postUpdatePluginParameter(controlID, controlValue, paramInfo);

	return true; /// handled
}

/**
\brief perform any operations after the plugin parameter has been updated; this is one paradigm for
	   transferring control information into vital plugin variables or member objects. If you use this
	   method you can decode the control ID and then do any cooking that is needed. NOTE: do not
	   overwrite bound variables here - this is ONLY for any extra cooking that is required to convert
	   the GUI data to meaninful coefficients or other specific modifiers.

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- now do any post update cooking; be careful with VST Sample Accurate automation
    //     If enabled, then make sure the cooking functions are short and efficient otherwise disable it
    //     for the Parameter involved
    switch(controlID)
    {
        case 0:
        {	
			// direct map to the a1 ff filter knob
			a1_left_ff_filter = a1_ff_filter_gui;
			a1_right_ff_filter = a1_ff_filter_gui;
			break;
        }

		case 2:
		{
			//freq
			cook_frequency();
			break;
		}

		case 10:
		{
			// direct map to the a0 ff filter knob
			a0_left_ff_filter = a0_ff_filter_gui;
			a0_right_ff_filter = a0_ff_filter_gui;
			break;
		}

		case 12:
		{	
			//if oscillator is started
			if (start_osc_gui == 1) {
				//reset(); //this caused a reset every ~66th sample period. 
				cook_frequency();
			}

			break;
		}

		case 20:
		{
			// direct map to the a0 fb filter knob
			a0_left_fb_filter = a0_fb_filter_gui;
			a0_right_fb_filter = a0_fb_filter_gui;
			break;
		}

		case 30:
		{
			// direct map to the b1 fb filter knob
			b1_left_fb_filter = b1_fb_filter_gui;
			b1_right_fb_filter = b1_fb_filter_gui;
			break;
		}

        default:
			break;
    }

	return true;

}

/**
\brief has nothing to do with actual variable or updated variable (binding)

CAUTION:
- DO NOT update underlying variables here - this is only for sending GUI updates or letting you
  know that a parameter was changed; it should not change the state of your plugin.

WARNING:
- THIS IS NOT THE PREFERRED WAY TO LINK OR COMBINE CONTROLS TOGETHER. THE PROPER METHOD IS
  TO USE A CUSTOM SUB-CONTROLLER THAT IS PART OF THE GUI OBJECT AND CODE.
  SEE http://www.willpirkle.com for more information

\param controlID the control ID value of the parameter being updated
\param actualValue the new control value

\return true if operation succeeds, false otherwise
*/
bool PluginCore::guiParameterChanged(int32_t controlID, double actualValue)
{
	/*
	switch (controlID)
	{
		case controlID::<your control here>
		{

			return true; // handled
		}

		default:
			break;
	}*/

	return false; /// not handled
}

/**
\brief For Custom View and Custom Sub-Controller Operations

NOTES:
- this is for advanced users only to implement custom view and custom sub-controllers
- see the SDK for examples of use

\param messageInfo a structure containing information about the incoming message

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMessage(MessageInfo& messageInfo)
{
	// --- decode message
	switch (messageInfo.message)
	{
		// --- add customization appearance here
	case PLUGINGUI_DIDOPEN:
	{
		return false;
	}

	// --- NULL pointers so that we don't accidentally use them
	case PLUGINGUI_WILLCLOSE:
	{
		return false;
	}

	// --- update view; this will only be called if the GUI is actually open
	case PLUGINGUI_TIMERPING:
	{
		return false;
	}

	// --- register the custom view, grab the ICustomView interface
	case PLUGINGUI_REGISTER_CUSTOMVIEW:
	{

		return false;
	}

	case PLUGINGUI_REGISTER_SUBCONTROLLER:
	case PLUGINGUI_QUERY_HASUSERCUSTOM:
	case PLUGINGUI_USER_CUSTOMOPEN:
	case PLUGINGUI_USER_CUSTOMCLOSE:
	case PLUGINGUI_EXTERNAL_SET_NORMVALUE:
	case PLUGINGUI_EXTERNAL_SET_ACTUALVALUE:
	{

		return false;
	}

	default:
		break;
	}

	return false; /// not handled
}


/**
\brief process a MIDI event

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param event a structure containing the MIDI event data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMIDIEvent(midiEvent& event)
{
	return true;
}

/**
\brief (for future use)

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param vectorJoysickData a structure containing joystick data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData)
{
	return true;
}

/**
\brief use this method to add new presets to the list

NOTES:
- see the SDK for examples of use
- for non RackAFX users that have large paramter counts, there is a secret GUI control you
  can enable to write C++ code into text files, one per preset. See the SDK or http://www.willpirkle.com for details

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginPresets()
{
	// **--0xFF7A--**

	// --- Plugin Presets 
	int index = 0;
	PresetInfo* preset = nullptr;

	// --- Preset: Factory Preset
	preset = new PresetInfo(index++, "Factory Preset");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::a1_ff_filter_gui, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::volume_gui, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::a0_ff_filter_gui, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::a0_fb_filter_gui, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::filter_selection_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::frequency_osc_gui, 440.000000);
	setPresetParameter(preset->presetParameters, controlID::start_osc_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::b1_fb_filter_gui, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_type_gui, 0.000000);
	addPreset(preset);


	// **--0xA7FF--**

    return true;
}

/**
\brief setup the plugin description strings, flags and codes; this is ordinarily done through the ASPiKreator or CMake

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginDescriptors()
{
    pluginDescriptor.pluginName = PluginCore::getPluginName();
    pluginDescriptor.shortPluginName = PluginCore::getShortPluginName();
    pluginDescriptor.vendorName = PluginCore::getVendorName();
    pluginDescriptor.pluginTypeCode = PluginCore::getPluginType();

	// --- describe the plugin attributes; set according to your needs
	pluginDescriptor.hasSidechain = kWantSidechain;
	pluginDescriptor.latencyInSamples = kLatencyInSamples;
	pluginDescriptor.tailTimeInMSec = kTailTimeMsec;
	pluginDescriptor.infiniteTailVST3 = kVSTInfiniteTail;

    // --- AAX
    apiSpecificInfo.aaxManufacturerID = kManufacturerID;
    apiSpecificInfo.aaxProductID = kAAXProductID;
    apiSpecificInfo.aaxBundleID = kAAXBundleID;  /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.aaxEffectID = "aaxDeveloper.";
    apiSpecificInfo.aaxEffectID.append(PluginCore::getPluginName());
    apiSpecificInfo.aaxPluginCategoryCode = kAAXCategory;

    // --- AU
    apiSpecificInfo.auBundleID = kAUBundleID;
	apiSpecificInfo.auBundleName = kAUBundleName;
	apiSpecificInfo.auBundleName = kAUBundleName;
	apiSpecificInfo.auBundleName = kAUBundleName;
	apiSpecificInfo.auBundleName = kAUBundleName;
	apiSpecificInfo.auBundleName = kAUBundleName;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.auBundleName = kAUBundleName;

    // --- VST3
    apiSpecificInfo.vst3FUID = PluginCore::getVSTFUID(); // OLE string format
    apiSpecificInfo.vst3BundleID = kVST3BundleID;/* MacOS only: this MUST match the bundle identifier in your info.plist file */
	apiSpecificInfo.enableVST3SampleAccurateAutomation = kVSTSAA;
	apiSpecificInfo.vst3SampleAccurateGranularity = kVST3SAAGranularity;

    // --- AU and AAX
    apiSpecificInfo.fourCharCode = PluginCore::getFourCharCode();

    return true;
}

// --- static functions required for VST3/AU only --------------------------------------------- //
const char* PluginCore::getPluginBundleName() { return kAUBundleName; }
const char* PluginCore::getPluginName(){ return kPluginName; }
const char* PluginCore::getShortPluginName(){ return kShortPluginName; }
const char* PluginCore::getVendorName(){ return kVendorName; }
const char* PluginCore::getVendorURL(){ return kVendorURL; }
const char* PluginCore::getVendorEmail(){ return kVendorEmail; }
const char* PluginCore::getAUCocoaViewFactoryName(){ return AU_COCOA_VIEWFACTORY_STRING; }
pluginType PluginCore::getPluginType(){ return kPluginType; }
const char* PluginCore::getVSTFUID(){ return kVSTFUID; }
int32_t PluginCore::getFourCharCode(){ return kFourCharCode; }


// --- user defined functions --------------------------------------------- //

void PluginCore::cook_frequency() 
{
	//inc = L*fd/fs

	inc = 1024.0 * frequency_osc_gui / getSampleRate();

	//Oscillation Rate = theta = wT = w/fs 
	//double wT = (kTwoPi*frequency_osc_gui)/getSampleRate();

	//coefficients according to design equations
	//b1_osc = -2.0 * cos(wT);
	//b2_osc = 1.0;

	//set initial conditions
	//y_z1_osc = sin(-1.0 * wT);	// sin(w(-1)T)
	//y_z2_osc = sin(-2.0 * wT);	// sin(w(-2)T)

	//re calculate new initial conditions
	//double wnT1 = asin(y_z1_osc);
	////find n
	//double n = wnT1 / wT;

	//asin will only return values from -pi/2 to pi/2 
	//(a sine wave in this range only includes a rising edge)
	//If we are on a rising edge, use the value 1T behind. 
	//On the other hand, on a falling edge the value 1T ahead is
	//equivalent to the 1T behind.
	//if (y_z1_osc > y_z2_osc)
	//	n -= 1;
	//else
	//	n += 1;

	////calculate the new sample
	//y_z2_osc = sin((n)*wT);
}


double PluginCore::linear_interpolation(double x1, double x2, double y1, double y2, double frac)
{
	double m = (y2 - y1) / (x2 - x1);

	double y = y2 - ( m * (x2 - frac));

	return y;
}
