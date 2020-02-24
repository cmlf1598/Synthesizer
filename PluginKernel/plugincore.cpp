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

	// --- continuous control: Vol Osc 1
	piParam = new PluginParameter(controlID::volume_osc_1_gui, "Vol Osc 1", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.707000, taper::kAntiLogTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&volume_osc_1_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Freq Osc 1
	piParam = new PluginParameter(controlID::frequency_osc_1_gui, "Freq Osc 1", "Hz", controlVariableType::kDouble, 25.000000, 4200.000000, 440.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&frequency_osc_1_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Start Osc 1
	piParam = new PluginParameter(controlID::start_osc_1_gui, "Start Osc 1", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&start_osc_1_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Osc 1 Type
	piParam = new PluginParameter(controlID::osc_1_type_gui, "Osc 1 Type", "sine,saw,tri,square", "sine");
	piParam->setBoundVariable(&osc_1_type_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Osc 1 Mode
	piParam = new PluginParameter(controlID::osc_1_mode_gui, "Osc 1 Mode", "normal,bandlimited", "normal");
	piParam->setBoundVariable(&osc_1_mode_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Start Osc 2
	piParam = new PluginParameter(controlID::start_osc_2_gui, "Start Osc 2", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&start_osc_2_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Freq Osc 2
	piParam = new PluginParameter(controlID::frequency_osc_2_gui, "Freq Osc 2", "Hz", controlVariableType::kDouble, 25.000000, 4200.000000, 440.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&frequency_osc_2_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Osc 2 Type
	piParam = new PluginParameter(controlID::osc_2_type_gui, "Osc 2 Type", "sine,saw,tri,square", "sine");
	piParam->setBoundVariable(&osc_2_type_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Osc 2 Mode
	piParam = new PluginParameter(controlID::osc_2_mode_gui, "Osc 2 Mode", "normal,bandlimited", "normal");
	piParam->setBoundVariable(&osc_2_mode_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Vol Osc 2
	piParam = new PluginParameter(controlID::volume_osc_2_gui, "Vol Osc 2", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.707000, taper::kAntiLogTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&volume_osc_2_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Start LFO 1
	piParam = new PluginParameter(controlID::start_LFO_1_gui, "Start LFO 1", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&start_LFO_1_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Start LFO 2
	piParam = new PluginParameter(controlID::start_LFO_2_gui, "Start LFO 2", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&start_LFO_2_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Freq LFO 1
	piParam = new PluginParameter(controlID::frequency_LFO_1_gui, "Freq LFO 1", "Hz", controlVariableType::kDouble, 0.100000, 20.000000, 10.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&frequency_LFO_1_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Freq LFO 2
	piParam = new PluginParameter(controlID::frequency_LFO_2_gui, "Freq LFO 2", "Hz", controlVariableType::kDouble, 0.100000, 20.000000, 10.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&frequency_LFO_2_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Gain
	piParam = new PluginParameter(controlID::gain_control_filter_gui, "Gain", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&gain_control_filter_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Cut-off freq
	piParam = new PluginParameter(controlID::COF_control_filter_gui, "Cut-off freq", "Hz", controlVariableType::kDouble, 25.000000, 4200.000000, 440.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(20.00);
	piParam->setBoundVariable(&COF_control_filter_gui, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: LFO 1 control
	piParam = new PluginParameter(controlID::LFO_1_control_gui, "LFO 1 control", "AM,FM", "AM");
	piParam->setBoundVariable(&LFO_1_control_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO 2 control
	piParam = new PluginParameter(controlID::LFO_2_control_gui, "LFO 2 control", "AM,FM", "AM");
	piParam->setBoundVariable(&LFO_2_control_gui, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::volume_osc_1_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483702);
	setParamAuxAttribute(controlID::volume_osc_1_gui, auxAttribute);

	// --- controlID::frequency_osc_1_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483680);
	setParamAuxAttribute(controlID::frequency_osc_1_gui, auxAttribute);

	// --- controlID::start_osc_1_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::start_osc_1_gui, auxAttribute);

	// --- controlID::osc_1_type_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::osc_1_type_gui, auxAttribute);

	// --- controlID::osc_1_mode_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::osc_1_mode_gui, auxAttribute);

	// --- controlID::start_osc_2_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::start_osc_2_gui, auxAttribute);

	// --- controlID::frequency_osc_2_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483680);
	setParamAuxAttribute(controlID::frequency_osc_2_gui, auxAttribute);

	// --- controlID::osc_2_type_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::osc_2_type_gui, auxAttribute);

	// --- controlID::osc_2_mode_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::osc_2_mode_gui, auxAttribute);

	// --- controlID::volume_osc_2_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483702);
	setParamAuxAttribute(controlID::volume_osc_2_gui, auxAttribute);

	// --- controlID::start_LFO_1_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::start_LFO_1_gui, auxAttribute);

	// --- controlID::start_LFO_2_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::start_LFO_2_gui, auxAttribute);

	// --- controlID::frequency_LFO_1_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483680);
	setParamAuxAttribute(controlID::frequency_LFO_1_gui, auxAttribute);

	// --- controlID::frequency_LFO_2_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483680);
	setParamAuxAttribute(controlID::frequency_LFO_2_gui, auxAttribute);

	// --- controlID::gain_control_filter_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483702);
	setParamAuxAttribute(controlID::gain_control_filter_gui, auxAttribute);

	// --- controlID::COF_control_filter_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483702);
	setParamAuxAttribute(controlID::COF_control_filter_gui, auxAttribute);

	// --- controlID::LFO_1_control_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::LFO_1_control_gui, auxAttribute);

	// --- controlID::LFO_2_control_gui
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::LFO_2_control_gui, auxAttribute);


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
	
	//Gain control filter
	alfa_gain_control_filter = 1.0;
	a0_gain_control_filter = gain_control_filter_gui;
	z1_gain_control_filter = 0.0;

	//Cutoff control filter

	fc_COF_control_filter = COF_control_filter_gui;
	z1_x_COF_control_filter = 0.0;
	z1_y_COF_control_filter = 0.0;

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

	//setup arrays 
	// maxes used for normalization
	double max_tri = 0;
	double max_saw = 0;
	double max_sqr = 0;


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
		if (i == 1)
			square_array[i] = 0.0;
		else 
			square_array[i] = i < 512 ? +1.0 : -1.0;

		//zero at the start of each
		saw_tooth_array_bl5[i] = 0.0;
		triangle_array_bl5[i] = 0.0;
		square_array_bl5[i] = 0.0;

		// sawtooth harmonics
		for (int g = 1; g <= 6; g++) 
		{
			double n = (double) g;
			saw_tooth_array_bl5[i] += pow(-1.0, g + 1) * (1.0 / n) * sin(kTwoPi * i * n / 1024.0);
		}

		// triangle harmonics
		for (int g = 0; g <= 3; g++)
		{
			double n = (double) g;
			triangle_array_bl5[i] += pow(-1.0, g) * (1.0 / pow((2 * n + 1), 2)) * sin(kTwoPi * (2.0 * n + 1) * i / 1024.0);
		}

		// square harmonics
		for (int g = 1; g <= 5; g += 2)
		{
			double n = double(g);
			square_array_bl5[i] += (1.0 / n) * sin(kTwoPi * i * n / 1024.0);
		}

		if (i == 0)
		{
			max_saw = saw_tooth_array_bl5[i];
			max_tri = triangle_array_bl5[i];
			max_sqr = square_array_bl5[i];
		}
		else
		{
			//test and store
			if (saw_tooth_array_bl5[i] > max_saw)
				max_saw = saw_tooth_array_bl5[i];

			if (triangle_array_bl5[i] > max_tri)
				max_tri = triangle_array_bl5[i];

			if (square_array_bl5[i] > max_sqr)
				max_sqr = square_array_bl5[i];
		}
	}

	//normalize the bandlimited tables
	for (int i = 0; i < 1024; i++)
	{
		//normalize it
		saw_tooth_array_bl5[i] /= max_saw;
		triangle_array_bl5[i] /= max_tri;
		square_array_bl5[i] /= max_sqr;
	}


	// clear variables 
	reset();
	inc_osc_1 = 0.0;
	inc_osc_2 = 0.0;
	inc_LFO_1 = 0.0;
	inc_LFO_2 = 0.0;

	// initialize inc
	inc_osc_1 = cook_frequency_osc(frequency_osc_1_gui);
	inc_osc_2 = cook_frequency_osc(frequency_osc_2_gui);
	inc_LFO_1 = cook_frequency_osc(frequency_LFO_1_gui);
	inc_LFO_2 = cook_frequency_osc(frequency_LFO_2_gui);

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

	double AM_final_out_sample;
	double AM_1_out_sample;
	double AM_2_out_sample;
	double gain_control_sample;
	double final_out_sample;

	double in_btw_sample_1;

	//Gain control Filter 
	double xn_gain_control_filter;
	double xn_1_gain_control_filter;
	double yn_gain_control_filter;

	//Cut-off frequency control filter
	double xn_COF_control_filter;
	double xn_1_COF_control_filter;
	double yn_COF_control_filter;
	double yn_1_COF_control_filter;

	//Volume
	

    // --- decode the channelIOConfiguration and process accordingly
    //
	// --- Synth Plugin:
	// --- Synth Plugin --- remove for FX plugins

	if (getPluginType() == kSynthPlugin)
	{
		// --- output silence: change this with your signal render code
		if ( (start_osc_1_gui == 0) && (start_osc_2_gui == 0) )
		{
			processFrameInfo.audioOutputFrame[0] = 0.0;
			if (processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
				processFrameInfo.audioOutputFrame[1] = 0.0;

			return true;	/// processed
		}

		//intermediate variables
		double yn_osc_1 = 0;
		double yn_osc_2 = 0;
		double yn_LFO_1 = 0;
		double yn_LFO_2 = 0;

		
		//call the LFO function
		do_LFO(&yn_LFO_1, &yn_LFO_2);

		//FM

		if ((start_LFO_1_gui == 1) && (compareEnumToInt(LFO_1_control_guiEnum::FM, LFO_1_control_gui)))
		{
			inc_osc_1 = cook_frequency_osc(frequency_osc_1_gui + (20.0 * yn_LFO_1));
		}

		if ((start_LFO_2_gui == 1) && (compareEnumToInt(LFO_2_control_guiEnum::FM, LFO_2_control_gui)))
		{
			inc_osc_2 = cook_frequency_osc(frequency_osc_2_gui + (20.0 * yn_LFO_2));
		}

		//call the oscillator function
		do_oscillate(&yn_osc_1, &yn_osc_2);
		
		//AM
		if ((start_LFO_1_gui == 1) && (compareEnumToInt(LFO_1_control_guiEnum::AM, LFO_1_control_gui)))
		{
			AM_1_out_sample = yn_LFO_1  * yn_osc_1;
		}
		else
		{
			AM_1_out_sample = yn_osc_1;
		}

		if ((start_LFO_2_gui == 1) && (compareEnumToInt(LFO_2_control_guiEnum::AM, LFO_2_control_gui)))
		{
			AM_2_out_sample = yn_LFO_2  * yn_osc_2;
		}
		else
		{
			AM_2_out_sample = yn_osc_2;
		}

		AM_final_out_sample = (volume_osc_1_gui/2) * AM_1_out_sample + (volume_osc_2_gui/2) * AM_2_out_sample;
		in_btw_sample_1 = AM_final_out_sample;


		//Gain control filter 

		// Input sample is x(n)
		xn_gain_control_filter = in_btw_sample_1;
		//Delay sample is x(n - 1)
		xn_1_gain_control_filter = z1_gain_control_filter;
		//Difference equation
		yn_gain_control_filter = (a0_gain_control_filter * xn_gain_control_filter) + (alfa_gain_control_filter * xn_1_gain_control_filter);
		//Delay with current x(n)
		z1_gain_control_filter = xn_gain_control_filter;
		
		gain_control_sample = yn_gain_control_filter;

		//COF control filter
		
		//For the Lowpass Filter
		xn_COF_control_filter = gain_control_sample;
		xn_1_COF_control_filter = z1_x_COF_control_filter;
		yn_1_COF_control_filter = z1_y_COF_control_filter;
		yn_COF_control_filter = b0_COF_control_filter * xn_COF_control_filter + b1_COF_control_filter * xn_1_COF_control_filter
			- a1_COF_control_filter * yn_1_COF_control_filter;
		z1_x_COF_control_filter = xn_COF_control_filter;
		z1_y_COF_control_filter = yn_COF_control_filter;

		final_out_sample = yn_COF_control_filter;

		//write out
		processFrameInfo.audioOutputFrame[0] = final_out_sample;
		if (processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
			processFrameInfo.audioOutputFrame[1] = final_out_sample;

		return true;	/// processed

	}



	

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing
		return true; /// processed
		
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		
		return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		
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
        
		case 10:
		{
			//if oscillator 1 is started
			if (start_osc_1_gui == 1) 
				//reset(); //this caused a reset every ~66th sample period. 
				inc_osc_1 = cook_frequency_osc(frequency_osc_1_gui);
			break;
		}


		case 12:
		{	
			//freq
			inc_osc_1 = cook_frequency_osc(frequency_osc_1_gui);
			break;
		}


		case 17:
		{
			//if LFO 1 is started
			if (start_LFO_1_gui == 1) {
				inc_LFO_1 = cook_frequency_osc(frequency_LFO_1_gui);
			}

			break;
		}

		case 18:
		{
			//freq
			inc_LFO_1 = cook_frequency_osc(frequency_LFO_1_gui);
			break;
		}


		case 20:
		{
			//if oscillator 2 is started
			if (start_osc_2_gui == 1) 
				//reset(); //this caused a reset every ~66th sample period. 
				inc_osc_2 = cook_frequency_osc(frequency_osc_2_gui);
			break;
		}

		case 22:
		{
			//freq
			inc_osc_2 = cook_frequency_osc(frequency_osc_2_gui);
			break;
		}

		case 27:
		{
			//if LFO 2 is started
			if (start_LFO_2_gui == 1) 
				inc_LFO_2 = cook_frequency_osc(frequency_LFO_2_gui);
			break;
		}

		case 28:
		{
			//freq
			inc_LFO_2 = cook_frequency_osc(frequency_LFO_2_gui);
			break;
		}

		case 41:
		{
			//freq
			a0_gain_control_filter = gain_control_filter_gui;
			break;
		}

		case 51:
		{	
			fc_COF_control_filter = COF_control_filter_gui;
			K_COF_control_filter = tan((kTwoPi * fc_COF_control_filter) / getSampleRate());
			b0_COF_control_filter = K_COF_control_filter / (K_COF_control_filter + 1);
			b1_COF_control_filter = b0_COF_control_filter;
			a1_COF_control_filter = (K_COF_control_filter - 1) / (K_COF_control_filter + 1);
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
	setPresetParameter(preset->presetParameters, controlID::volume_osc_1_gui, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::frequency_osc_1_gui, 440.000000);
	setPresetParameter(preset->presetParameters, controlID::start_osc_1_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_1_type_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_1_mode_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::start_osc_2_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::frequency_osc_2_gui, 440.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_2_type_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::osc_2_mode_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::volume_osc_2_gui, 0.707000);
	setPresetParameter(preset->presetParameters, controlID::start_LFO_1_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::start_LFO_2_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::frequency_LFO_1_gui, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::frequency_LFO_2_gui, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::gain_control_filter_gui, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::COF_control_filter_gui, 440.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_1_control_gui, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFO_2_control_gui, -0.000000);
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

double PluginCore::cook_frequency_osc(double frequency_osc) 
{
	//inc = L*fd/fs
	double inc_osc = 0.0;
	inc_osc = 1024.0 * frequency_osc / getSampleRate();
	return inc_osc;
}


double PluginCore::linear_interpolation(double x1, double x2, double y1, double y2, double frac)
{
	double m = (y2 - y1) / (x2 - x1);

	double y = y2 - ( m * (x2 - frac));

	return y;
}

void PluginCore::do_oscillate(double *yn_1, double *yn_2)
{
	*yn_1 = 0.0;
	*yn_2 = 0.0;

	//Oscillator 1
	double out_sample_osc_1;
	int int_read_index_osc_1;
	double frac_read_index_osc_1;
	int int_read_index_next_osc_1;

	//Oscillator 2
	double out_sample_osc_2;
	int int_read_index_osc_2;
	double frac_read_index_osc_2;
	int int_read_index_next_osc_2;

	// output value for this cycle
	out_sample_osc_1 = 0;
	out_sample_osc_2 = 0;

	// get integer part
	int_read_index_osc_1 = (int)read_index_osc_1;
	int_read_index_osc_2 = (int)read_index_osc_2;

	//get fractional part
	frac_read_index_osc_1 = read_index_osc_1 - (double)int_read_index_osc_1;
	frac_read_index_osc_2 = read_index_osc_2 - (double)int_read_index_osc_2;

	//second index for interpolation: wrap around buffer if needed
	int_read_index_next_osc_1 = int_read_index_osc_1 + 1 > 1023 ? 0 : int_read_index_osc_1 + 1;
	int_read_index_next_osc_2 = int_read_index_osc_2 + 1 > 1023 ? 0 : int_read_index_osc_2 + 1;

	// interpolate the output

	//Oscillator 1
	if (start_osc_1_gui == 1) {
		if (compareEnumToInt(osc_1_type_guiEnum::sine, osc_1_type_gui))
			//sine
			out_sample_osc_1 = linear_interpolation(0.0, 1.0, sin_array[int_read_index_osc_1], sin_array[int_read_index_next_osc_1], frac_read_index_osc_1);
		else if (compareEnumToInt(osc_1_type_guiEnum::saw, osc_1_type_gui))
			//saw
			if (compareEnumToInt(osc_1_mode_guiEnum::normal, osc_1_mode_gui))
				out_sample_osc_1 = linear_interpolation(0.0, 1.0, saw_tooth_array[int_read_index_osc_1], saw_tooth_array[int_read_index_next_osc_1], frac_read_index_osc_1);
			else
				out_sample_osc_1 = linear_interpolation(0.0, 1.0, saw_tooth_array_bl5[int_read_index_osc_1], saw_tooth_array_bl5[int_read_index_next_osc_1], frac_read_index_osc_1);
		else if (compareEnumToInt(osc_1_type_guiEnum::tri, osc_1_type_gui))
			//triangular
			if (compareEnumToInt(osc_1_mode_guiEnum::normal, osc_1_mode_gui))
				out_sample_osc_1 = linear_interpolation(0.0, 1.0, triangle_array[int_read_index_osc_1], triangle_array[int_read_index_next_osc_1], frac_read_index_osc_1);
			else
				out_sample_osc_1 = linear_interpolation(0.0, 1.0, triangle_array_bl5[int_read_index_osc_1], triangle_array_bl5[int_read_index_next_osc_1], frac_read_index_osc_1);
		else if (compareEnumToInt(osc_1_type_guiEnum::square, osc_1_type_gui))
			//square
			if (compareEnumToInt(osc_1_mode_guiEnum::normal, osc_1_mode_gui))
				out_sample_osc_1 = linear_interpolation(0.0, 1.0, square_array[int_read_index_osc_1], square_array[int_read_index_next_osc_1], frac_read_index_osc_1);
			else
				out_sample_osc_1 = linear_interpolation(0.0, 1.0, square_array_bl5[int_read_index_osc_1], square_array_bl5[int_read_index_next_osc_1], frac_read_index_osc_1);
	}

	//Oscillator 2
	if (start_osc_2_gui == 1) {
		if (compareEnumToInt(osc_2_type_guiEnum::sine, osc_2_type_gui))
			//sine
			out_sample_osc_2 = linear_interpolation(0.0, 1.0, sin_array[int_read_index_osc_2], sin_array[int_read_index_next_osc_2], frac_read_index_osc_2);
		else if (compareEnumToInt(osc_2_type_guiEnum::saw, osc_2_type_gui))
			//saw
			if (compareEnumToInt(osc_2_mode_guiEnum::normal, osc_2_mode_gui))
				out_sample_osc_2 = linear_interpolation(0.0, 1.0, saw_tooth_array[int_read_index_osc_2], saw_tooth_array[int_read_index_next_osc_2], frac_read_index_osc_2);
			else
				out_sample_osc_2 = linear_interpolation(0.0, 1.0, saw_tooth_array_bl5[int_read_index_osc_2], saw_tooth_array_bl5[int_read_index_next_osc_2], frac_read_index_osc_2);
		else if (compareEnumToInt(osc_2_type_guiEnum::tri, osc_2_type_gui))
			//triangular
			if (compareEnumToInt(osc_2_mode_guiEnum::normal, osc_2_mode_gui))
				out_sample_osc_2 = linear_interpolation(0.0, 1.0, triangle_array[int_read_index_osc_2], triangle_array[int_read_index_next_osc_2], frac_read_index_osc_2);
			else
				out_sample_osc_2 = linear_interpolation(0.0, 1.0, triangle_array_bl5[int_read_index_osc_2], triangle_array_bl5[int_read_index_next_osc_2], frac_read_index_osc_2);
		else if (compareEnumToInt(osc_2_type_guiEnum::square, osc_2_type_gui))
			//square
			if (compareEnumToInt(osc_2_mode_guiEnum::normal, osc_2_mode_gui))
				out_sample_osc_2 = linear_interpolation(0.0, 1.0, square_array[int_read_index_osc_2], square_array[int_read_index_next_osc_2], frac_read_index_osc_2);
			else
				out_sample_osc_2 = linear_interpolation(0.0, 1.0, square_array_bl5[int_read_index_osc_2], square_array_bl5[int_read_index_next_osc_2], frac_read_index_osc_2);
	}

	// add increment 
	read_index_osc_1 += inc_osc_1;
	read_index_osc_2 += inc_osc_2;

	//check the wrap
	if (read_index_osc_1 > 1024.0)
		read_index_osc_1 = read_index_osc_1 - 1024.0;
	if (read_index_osc_2 > 1024.0)
		read_index_osc_2 = read_index_osc_2 - 1024.0;

	//write out 
	*yn_1 = out_sample_osc_1;
	*yn_2 = out_sample_osc_2;
}

void PluginCore::do_LFO(double* yn_1, double* yn_2)
{
	*yn_1 = 0.0;
	*yn_2 = 0.0;

	//Oscillator 1
	double out_sample_LFO_1;
	int int_read_index_LFO_1;
	double frac_read_index_LFO_1;
	int int_read_index_next_LFO_1;

	//Oscillator 2
	double out_sample_LFO_2;
	int int_read_index_LFO_2;
	double frac_read_index_LFO_2;
	int int_read_index_next_LFO_2;

	// output value for this cycle
	out_sample_LFO_1 = 0;
	out_sample_LFO_2 = 0;

	// get integer part
	int_read_index_LFO_1 = (int)read_index_LFO_1;
	int_read_index_LFO_2 = (int)read_index_LFO_2;

	//get fractional part
	frac_read_index_LFO_1 = read_index_LFO_1 - (double)int_read_index_LFO_1;
	frac_read_index_LFO_2 = read_index_LFO_2 - (double)int_read_index_LFO_2;

	//second index for interpolation: wrap around buffer if needed
	int_read_index_next_LFO_1 = int_read_index_LFO_1 + 1 > 1023 ? 0 : int_read_index_LFO_1 + 1;
	int_read_index_next_LFO_2 = int_read_index_LFO_2 + 1 > 1023 ? 0 : int_read_index_LFO_2 + 1;

	// interpolate the output

	//LFO 1
	if (start_LFO_1_gui == 1) {

		//sine
		out_sample_LFO_1 = linear_interpolation(0.0, 1.0, sin_array[int_read_index_LFO_1], sin_array[int_read_index_next_LFO_1], frac_read_index_LFO_1);
		
	}

	//Oscillator 2
	if (start_osc_2_gui == 1) {

		//sine
		out_sample_LFO_2 = linear_interpolation(0.0, 1.0, sin_array[int_read_index_LFO_2], sin_array[int_read_index_next_LFO_2], frac_read_index_LFO_2);
		
	}

	// add increment 
	read_index_LFO_1 += inc_LFO_1;
	read_index_LFO_2 += inc_LFO_2;

	//check the wrap
	if (read_index_LFO_1 > 1024.0)
		read_index_LFO_1 = read_index_LFO_1 - 1024.0;
	if (read_index_LFO_2 > 1024.0)
		read_index_LFO_2 = read_index_LFO_2 - 1024.0;

	//write out 
	*yn_1 = out_sample_LFO_1;
	*yn_2 = out_sample_LFO_2;
}
