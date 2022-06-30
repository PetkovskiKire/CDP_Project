#include "Buttons.h"

using namespace SZVSlib;
using namespace std;
/*!
  \class SZVSlib::Buttons
  \inmodule SZVSlib

  \section1 Usage

  Add documentation for Buttons here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
Buttons::Buttons()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
Buttons::~Buttons()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void Buttons::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    ImePrezimeOutput.Create("ImePrezimeOutput",this);
    ImePrezimeInput.Create("ImePrezimeInput",this);
    Selektirano.Create("Selektirano",this);
    Pauza.Create("Pauza",this);
    SluzbenIzlez.Create("SluzbenIzlez",this);
    PrivatenIzlez.Create("PrivatenIzlez",this);
    Izlez.Create("Izlez",this);
    Vlez.Create("Vlez",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void Buttons::CreateModel()
{
    CDPComponent::CreateModel();

    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&Buttons::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void Buttons::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);

    myTimer.Reset( 15.0 );    // Set timeout value in seconds
    myTimer.Start();          // Will start timing from now
    ImePrezime = "----------                      ";
    pomni = "----------";
    flag = true;
    vlez = true;

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
void Buttons::ProcessNull()
{
    if (myTimer.TimedOut())
    {
      ImePrezime = "----------                      ";
      pomni = "----------";
      flag = true;
      vlez = true;

      ImePrezimeOutput.SetVariantValue(ImePrezime);
      Selektirano.SetVariantValue(pomni);
      ImePrezimeInput.SetVariantValue(ImePrezime);

      myTimer.Restart();    // Start new timing cycle

    }
    else
    {
      if (flag == false){                                               //click button

          ImePrezime = ImePrezimeInput;                                 //then read input
          Selektirano.SetVariantValue(pomni);
        //  vlez = false;
          ImePrezimeOutput.SetVariantValue(ImePrezime);

      }
    }


   if(Izlez)
   {
       if(flag){
          pomni = "Izlez";
          myTimer.Restart();
          flag = false;
       }
   }

   if(Vlez)
   {
       if(flag){
          pomni = "Vlez";
          myTimer.Restart();
          flag = false;
       }
   }

   if(Pauza)
   {
       if(flag){
          pomni = "Pauza";
          myTimer.Restart();
          flag = false;
       }
   }

   if(PrivatenIzlez)
   {
       if(flag){
          pomni = "Privaten izlez";
          myTimer.Restart();
          flag = false;
       }
   }

   if(SluzbenIzlez)
   {
       if(flag){
          pomni = "Sluzben izlez";
          myTimer.Restart();
          flag = false;
       }
   }
}
