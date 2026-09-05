<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:template name="addDirectives">
        <xsl:param name="indent" select="''"/>

        <xsl:value-of select="$indent"/>
        <xsl:text>#</xsl:text>
        <xsl:value-of select="name()"/>

        <xsl:if test="@cond">
            <xsl:text> </xsl:text>
            <xsl:value-of select="@cond"/>
        </xsl:if>

        <xsl:text>&#xA;</xsl:text>
    </xsl:template>

	<xsl:template name="addFunctionTableSetter">
		<xsl:param name="prefix"/>
		<xsl:text>static </xsl:text>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>FunctionTable next = { 0 };&#xA;&#xA;</xsl:text>

		<xsl:text>const </xsl:text>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>FunctionTable* </xsl:text>
		<xsl:value-of select="$prefix"/>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>setFunctions(const </xsl:text>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>FunctionTable* a, </xsl:text>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>FunctionTable* b) {&#xA;    </xsl:text>
		<xsl:text>memcpy(&amp;next, a, sizeof(next));

	if (!b) return &amp;next;

    for (size_t offset = 0; offset &lt; sizeof(</xsl:text><xsl:value-of select="registry/functionPrefix"/><xsl:text>FunctionTable); offset += sizeof(void*)) {
        bs_Callback* f_a = ((unsigned char*)&amp;next) + offset;
        bs_Callback* f_b = ((unsigned char*)b) + offset;
        if (!*f_a)
            *f_a = *f_b;
    }

    return &amp;next;
}

</xsl:text>
	</xsl:template>

	<xsl:template name="addFunctionTableGetter">
		<xsl:param name="prefix"/>

		<xsl:text>static inline </xsl:text>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>FunctionTable* </xsl:text>
		<xsl:value-of select="$prefix"/>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>getFunctions() {&#xA;    </xsl:text>

		<xsl:text>static </xsl:text>
		<xsl:value-of select="registry/functionPrefix"/>
		<xsl:text>FunctionTable functions;&#xA;&#xA;</xsl:text>

		<xsl:for-each select="registry/functions/function">
			<xsl:if test="not(body) or @type = 'allowBody'">
				<xsl:text>    functions.</xsl:text>
				<xsl:value-of select="@name"/>
				<xsl:text> = </xsl:text>
				<xsl:value-of select="$prefix"/>
				<xsl:value-of select="@name"/>
				<xsl:text>;&#xA;</xsl:text>
			</xsl:if>
		</xsl:for-each>

		<xsl:text>&#xA;    return &amp;functions;&#xA;</xsl:text>

		<xsl:text>}&#xA;&#xA;</xsl:text>
	</xsl:template>

	<xsl:template name="addFunctionProcsGetter">
        <xsl:param name="prefix"/>

        <xsl:text>static inline </xsl:text>
        <xsl:value-of select="registry/functionPrefix"/>
        <xsl:text>FunctionTable* </xsl:text>
        <xsl:value-of select="$prefix"/>
        <xsl:value-of select="registry/functionPrefix"/>
        <xsl:text>getFunctions() {&#xA;    </xsl:text>

		<xsl:text>static </xsl:text>
		<xsl:value-of select="registry/functionPrefix"/>
        <xsl:text>FunctionTable functions;&#xA;&#xA;</xsl:text>

        <xsl:text>#ifdef _WIN32&#xA;</xsl:text>
        <xsl:text>#define bs_getProcAddress(module, name) GetProcAddress(module, name)&#xA;</xsl:text>

        <xsl:text>    HMODULE module = NULL;&#xA;</xsl:text>
        <xsl:text>    GetModuleHandleExA(&#xA;        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,&#xA;        (LPCSTR)(&amp;</xsl:text>
        <xsl:value-of select="concat(concat($prefix, registry/functionPrefix), 'getFunctions')"/>
        <xsl:text>),&#xA;        &amp;module);&#xA;&#xA;</xsl:text>

        <xsl:text>#else&#xA;</xsl:text>

        <xsl:text>    Dl_info module_info;&#xA;</xsl:text>
        <xsl:text>    void *module = NULL;&#xA;</xsl:text>
        <xsl:text>    dladdr((void *)(&amp;</xsl:text>
        <xsl:value-of select="concat(concat($prefix, registry/functionPrefix), 'getFunctions')"/>
        <xsl:text>), &amp;module_info);&#xA;</xsl:text>
        <xsl:text>    module = dlopen(module_info.dli_fname, RTLD_LAZY);&#xA;</xsl:text>
        <xsl:text>#define bs_getProcAddress(module, name) dlsym(module, name)&#xA;</xsl:text>

        <xsl:text>#endif&#xA;</xsl:text>

        <xsl:for-each select="registry/functions/function">
			<xsl:if test="not(body) and not(@variadic)">
                <xsl:text>    functions.</xsl:text>
                <xsl:value-of select="@name"/>
                <xsl:text> = (PFN_</xsl:text>
                <xsl:value-of select="@name"/>
                <xsl:text>)bs_getProcAddress(module, "</xsl:text>
                <xsl:value-of select="$prefix"/>
                <xsl:value-of select="@name"/>
                <xsl:text>");&#xA;</xsl:text>
            </xsl:if>
        </xsl:for-each>

        <xsl:text>&#xA;    #undef bs_getProcAddress&#xA;</xsl:text>

        <xsl:text>#ifndef _WIN32&#xA;</xsl:text>
        <xsl:text>    dlclose(module);&#xA;</xsl:text>
        <xsl:text>#endif&#xA;</xsl:text>

        <xsl:text>    return &amp;functions;&#xA;</xsl:text>

        <xsl:text>}&#xA;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template name="add-license">
        <xsl:text>
 /**
  MIT License

  Copyright (c) 2026 switch360hardflip &lt;switch360hardflip@gmail.com&gt;

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */

 /**
  This file was generated from basilisk-gfx.com

  It is not recommended to make changes to this file as it will be lost if
  the code is regenerated.
  */

</xsl:text>
    </xsl:template>

	<xsl:template name="createFunctionBody">
		<xsl:param name="prefix"/>

		<xsl:value-of select="return"/>
		<xsl:text> </xsl:text>
		<xsl:value-of select="$prefix"/>
		<xsl:value-of select="@name"/>
		<xsl:text>(</xsl:text>

		<xsl:for-each select="param">
			<xsl:text>&#xA;    </xsl:text>
			<xsl:if test="type">
				<xsl:value-of select="type"/>
				<xsl:text> </xsl:text>
			</xsl:if>

			<xsl:value-of select="name"/>
			<xsl:for-each select="size">
				<xsl:text>[</xsl:text>
				<xsl:value-of select="."/>
				<xsl:text>]</xsl:text>
			</xsl:for-each>
			<xsl:if test="position() != last()">
				<xsl:text>, </xsl:text>
			</xsl:if>
		</xsl:for-each>
		<xsl:text>)&#xA;{&#xA;</xsl:text>

		<!-- Body -->
		<xsl:value-of select="body"/>

		<xsl:if test="not(body)">
			<xsl:text>    </xsl:text>
			<xsl:if test="not(return = 'void')">
				<xsl:text>return </xsl:text>
			</xsl:if>

			<xsl:text>next.</xsl:text>
			<xsl:value-of select="@name"/>
			<xsl:text>(</xsl:text>

			<xsl:for-each select="param">
				<xsl:value-of select="name"/>
				<xsl:if test="position() != last()">
					<xsl:text>, </xsl:text>
				</xsl:if>
			</xsl:for-each>
			<xsl:text>);</xsl:text>
		</xsl:if>

		<xsl:text>&#xA;}&#xA;&#xA;</xsl:text>
	</xsl:template>

</xsl:stylesheet>
