#pragma once

#include "CoreMinimal.h"

#include "Runtime/Online/HTTPServer/Public/HttpServerModule.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerRequest.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerResponse.h"
#include "Runtime/Online/HTTPServer/Public/HttpRouteHandle.h"
#include "Runtime/Online/HTTPServer/Public/IHttpRouter.h"


namespace UnrealHttpServer
{
	/**
	 * HTTP responser function
	 */
	typedef TFunction<TUniquePtr<FHttpServerResponse>(const FHttpServerRequest& Request)> FHttpResponser;

	class FWebUtil
	{
	public:	
		/**
		 * Bind a route with handler
		 */
		static FHttpRouteHandle BindRoute(const TSharedPtr<IHttpRouter>& HttpRouter, FString Path, const EHttpServerRequestVerbs& Verb, const FHttpResponser& HttpResponser);

		/**
		 * Create HTTP request handler (controller)
		 * In UE4, invoke OnComplete and return false will cause crash
		 * CreateHandler method is used to wrap the responser, in order to avoid the crash
		 */
		static FHttpRequestHandler CreateHandler(const FHttpResponser& HttpResponser);

		/**
		 * Get request json body, parse TArray<uint8> to TSharedPtr<FJsonObject>
		 */
		static TSharedPtr<FJsonObject> GetRequestJsonBody(const FHttpServerRequest& Request);

		/**
		 * Get Struct body (based on json body, the struct type should be UStruct)
		 */
		template <typename UStructType>
		static UStructType* GetRequestUStructBody(const FHttpServerRequest& Request);

		/**
		 * Success response (data & message)
		 */
		static TUniquePtr<FHttpServerResponse> SuccessResponse(TSharedPtr<FJsonObject> Data, FString Message);

		/**
		 * Success response (data only)
		 */
		static TUniquePtr<FHttpServerResponse> SuccessResponse(TSharedPtr<FJsonObject> Data);

		/**
		 * Success response (message only)
		 */
		static TUniquePtr<FHttpServerResponse> SuccessResponse(FString Message);

		/**
		 * Error response (data & message & code)
		 */
		static TUniquePtr<FHttpServerResponse> ErrorResponse(TSharedPtr<FJsonObject> Data, FString Message, int32 Code);

		/**
		 * Error response (data & message)
		 */
		static TUniquePtr<FHttpServerResponse> ErrorResponse(TSharedPtr<FJsonObject> Data, FString Message);

		/**
		 * Error response (message & code)
		 */
		static TUniquePtr<FHttpServerResponse> ErrorResponse(FString Message, int32 Code);

		/**
		 * Error response (message only)
		 */
		static TUniquePtr<FHttpServerResponse> ErrorResponse(FString Message);
	private:
		/* Success code in response body */
		static const int32 SUCCESS_CODE = 0;
		/* Default error code in response body */
		static const int32 DEFAULT_ERROR_CODE = -1;

		/**
		 * get verb string from enumerate (for logging use)
		 */
		static FString GetHttpVerbStringFromEnum(const EHttpServerRequestVerbs& Verb);

		/**
		 * Create json response from data, message, success status and user defined error code
		 */
		static TUniquePtr<FHttpServerResponse> JsonResponse(TSharedPtr<FJsonObject> Data, FString Message, bool Success, int32 Code);

		/**
		 * Check if the body content will be parsed as UTF-8 json by header
		 */
		static bool IsUTF8JsonRequestContent(const FHttpServerRequest& Request);
	};
}