#include "StdAfx.h"
#include "ScriptParser.h"

#include "CmdCamera.h"
#include "CmdDrawPixel.h"
#include "CmdViewport.h"
#include "States.h"
#include "Primitives.h"
#include "Matrix2D.h"
#include "Matrix3D.h"
#include "CmdLightCommands.h"

CScriptParser::CScriptParser(void)
{
	// Initialize dictionary

	// rasterization commands
	m_CommandDictionary.insert( std::make_pair( CString("drawpixel"),         new CCmdDrawPixel       ) );
    m_CommandDictionary.insert( std::make_pair( CString("color"),             new CCmdColor           ) );
    m_CommandDictionary.insert( std::make_pair( CString("drawbegin"),         new CCmdDrawbegin       ) );
    m_CommandDictionary.insert( std::make_pair( CString("drawend"),           new CCmdDrawend         ) );
    m_CommandDictionary.insert( std::make_pair( CString("fillmode"),          new CCmdFillmode        ) );

    // for specifying points, either 2D or 3D
    m_CommandDictionary.insert( std::make_pair( CString("vertex2"),           new CCmdVertex2         ) );
    m_CommandDictionary.insert( std::make_pair( CString("vertex3"),           new CCmdVertex3         ) );

    // camera, viewport and clipping commands
    m_CommandDictionary.insert( std::make_pair( CString("viewport"),          new CCmdViewport        ) );
    m_CommandDictionary.insert( std::make_pair( CString("showviewport"),      new CCmdShowviewport    ) );
    m_CommandDictionary.insert( std::make_pair( CString("clip"),              new CCmdSetClipping     ) );
    m_CommandDictionary.insert( std::make_pair( CString("backfacecull"),      new CCmdSetBackfaceCull ) );
    m_CommandDictionary.insert( std::make_pair( CString("zbuffer"),           new CCmdSetZBuffering   ) );
    m_CommandDictionary.insert( std::make_pair( CString("camerapersp"),       new CCmdCameraPersp     ) );
    m_CommandDictionary.insert( std::make_pair( CString("camerafov"),         new CCmdCameraFOV       ) );
    m_CommandDictionary.insert( std::make_pair( CString("cameranear"),        new CCmdNearPlane       ) );
    m_CommandDictionary.insert( std::make_pair( CString("camerafar"),         new CCmdFarPlane        ) );

    // 2D Matrix commands
    m_CommandDictionary.insert( std::make_pair( CString("matrix2didentity"),  new CCmdMat2DIdentity   ) );
    m_CommandDictionary.insert( std::make_pair( CString("matrix2dtranslate"), new CCmdMat2DTranslate  ) );
    m_CommandDictionary.insert( std::make_pair( CString("matrix2dscale"),     new CCmdMat2DScale      ) );
    m_CommandDictionary.insert( std::make_pair( CString("matrix2drotate"),    new CCmdMat2DRotate     ) );
    m_CommandDictionary.insert( std::make_pair( CString("matrix2dshear"),     new CCmdMat2DShear      ) );

    // 3D Matrix commands
    m_CommandDictionary.insert( std::make_pair( CString("matrix3didentity"),  new CCmdMat3DIdentity   ) );
    m_CommandDictionary.insert( std::make_pair( CString("matrix3dtranslate"), new CCmdMat3DTranslate  ) );
    m_CommandDictionary.insert( std::make_pair( CString("matrix3dscale"),     new CCmdMat3DScale      ) );
    m_CommandDictionary.insert( std::make_pair( CString("matrix3drotate"),    new CCmdMat3DRotate     ) );

	//Light commmands
	m_CommandDictionary.insert(std::make_pair(CString("worldambient"), new CCmdWorldAmbient));
	m_CommandDictionary.insert(std::make_pair(CString("lightambient"), new CCmdLightAmbient));
	m_CommandDictionary.insert(std::make_pair(CString("lightdiffuse"), new CCmdLightDiffuse));
	m_CommandDictionary.insert(std::make_pair(CString("lightspecular"), new CCmdLightSpecular));
	m_CommandDictionary.insert(std::make_pair(CString("attenconstant"), new CCmdAttenConstant));
	m_CommandDictionary.insert(std::make_pair(CString("attenlinear"), new CCmdAttenLinear));
	m_CommandDictionary.insert(std::make_pair(CString("attenquadratic"), new CCmdAttenQuadratic));
	m_CommandDictionary.insert(std::make_pair(CString("directionallight"), new CCmdDirectionalLight));
	m_CommandDictionary.insert(std::make_pair(CString("pointlight"), new CCmdPointLight));
	m_CommandDictionary.insert(std::make_pair(CString("spotlight"), new CCmdSpotLight));
	m_CommandDictionary.insert(std::make_pair(CString("clearlights"), new CCmdClearLights));
}

CScriptParser::~CScriptParser(void)
{
	// Delete dictionary memory
	while( m_CommandDictionary.begin() != m_CommandDictionary.end() )
    {
		delete m_CommandDictionary.begin()->second;
        m_CommandDictionary.erase( m_CommandDictionary.begin() );
    }
}

// Split given input string into a string list, using given "splitString" as the separators
void CScriptParser::StringSplit( CStringList &result, CString &inputString, CString &splitter )
{
	int splitterLength = splitter.GetLength();
	CString choppedString = inputString;
	
	// Split string
	int splitPos = choppedString.Find( splitter );
	while ( splitPos != -1 )
	{
		CString word = choppedString.Left( splitPos );
		if ( !word.IsEmpty() )
		{
			result.AddTail( word );
		}
		choppedString = choppedString.Right( choppedString.GetLength() - splitPos - splitterLength );
		splitPos = choppedString.Find( splitter );
	}

	// Add last word
	if ( !choppedString.IsEmpty() )
	{
		result.AddTail( choppedString );
	}
}

// Look up command in dictionary to return command object
CCmdCommand *CScriptParser::CommandLookup( CString &cmd )
{
	std::map<CString, CCmdCommand *>::const_iterator iter;
    iter = m_CommandDictionary.find( cmd.MakeLower() );
    if( iter != m_CommandDictionary.end() )
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

// Parse script into commands and parameters
void CScriptParser::ParseScript( CString &script )
{
	// Strip off Windows return characters
	script.Remove( '\r' );

	// Separate script into separate lines in a list
	CStringList commandLineList;
	CScriptParser::StringSplit( commandLineList, script, CString( '\n' ) );

	// For each command line, split out keyword and parameters
	POSITION pos;
	for( pos = commandLineList.GetHeadPosition(); pos != NULL; )
	{
		CommandLine command;

		CString line = commandLineList.GetNext( pos );
		int firstSpacePos = line.Find( ' ' );
		if ( firstSpacePos != -1 && firstSpacePos != 0 )
		{
			command.keyword = line.Left( firstSpacePos );
			command.params = line.Right( line.GetLength() - firstSpacePos - 1 );
		}
		else
		{
			command.keyword = line;
			command.params.Empty();
		}
		m_CommandLines.AddTail( command );
	}

	// Debug
	/*
	for( pos = m_CommandLines.GetHeadPosition(); pos != NULL; )
	{
		CommandLine cmdLine = m_CommandLines.GetNext( pos );
		CString str = CString("keyword: \"") + cmdLine.keyword + CString("\"");
		str = str + CString("\nparams: \"") + cmdLine.params + CString("\"");
		AfxMessageBox(str);
	}
	*/
}

void CScriptParser::ExecuteScript()
{
	// Execute script commands
	POSITION pos;
	for( pos = m_CommandLines.GetHeadPosition(); pos != NULL; )
	{
		CommandLine cmdLine = m_CommandLines.GetNext( pos );
		CCmdCommand *command = CommandLookup( cmdLine.keyword );
		if ( command != NULL )
		{
			command->execute( cmdLine.params );
		}
	}
}
