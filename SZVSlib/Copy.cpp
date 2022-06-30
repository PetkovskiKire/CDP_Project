#include "Copy.h"

using namespace SZVSlib;
using namespace std;
/*!
  \class SZVSlib::Copy
  \inmodule SZVSlib

  \section1 Usage

  Add documentation for Copy here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
Copy::Copy()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
Copy::~Copy()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void Copy::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    Output1.Create("Output1",this);
    Output2.Create("Output2",this);
    Input.Create("Input",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void Copy::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&Copy::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void Copy::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
}

/*!
 \brief Component Null state processing function

 Write your component's processing code here. When the component is simple, all the processing code may reside here.
 This function gets called periodically. The period is changed by setting the "fs" (frequency) Property when you use
 the component in a project.
 Functions called ProcessSTATENAME(), like ProcessNull(), are state processing functions and are only called when
 components are in given state. The default component state is "Null".
 Note, that state processing functions are not allowed to block (i.e. read files, sleep, communicate with network in
 blocking mode etc.) For blocking code use the 'Threaded Component Model' wizard instead.

 Please consult CDP Studio "Code Mode Manual" for more information and examples.
*/
void Copy::ProcessNull()
{
    /* Write your code here */
    std::string error = "/usr/local/lib/python3.9/dist-packages/mfrc522/MFRC522.py:151: RuntimeWarning: This channel is already in use, continuing anyway.  Use GPIO.setwarnings(False) to disable warnings.";
    std::string Copy = Input.GetVariantValue().ToString();


    if(!(Copy.compare(error))){
        Copy = "----------                      ";
    }

    Output1.SetVariantValue(Copy);
    Output2.SetVariantValue(Copy);
}
